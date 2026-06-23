#include "RsaSigner.hpp"
#include <windows.h>
#include <bcrypt.h>
#include <memory>

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

#pragma comment(lib, "bcrypt.lib")

namespace Uues::Core::Crypto {

class RsaSigner::Impl {
public:
    BCRYPT_ALG_HANDLE AlgHandle = nullptr;
    BCRYPT_KEY_HANDLE KeyHandle = nullptr;
    Dword KeyObjectLength = 0;
    std::unique_ptr<Byte[]> KeyObject;

    ~Impl() {
        if (KeyHandle) BCryptDestroyKey(KeyHandle);
        if (AlgHandle) BCryptCloseAlgorithmProvider(AlgHandle, 0);
    }
};

RsaSigner::RsaSigner() : mImpl(std::make_unique<Impl>()) {
    BCryptOpenAlgorithmProvider(&mImpl->AlgHandle, BCRYPT_RSA_ALGORITHM, nullptr, 0);
    BCryptSetProperty(mImpl->AlgHandle, L"PaddingScheme",
                      reinterpret_cast<PUCHAR>(const_cast<wchar_t*>(L"PKCS1")),
                      sizeof(L"PKCS1"), 0);
}

RsaSigner::~RsaSigner() = default;

bool RsaSigner::ImportPublicKey(const Common::ByteArray& KeyBlob) {
    if (mImpl->KeyHandle) {
        BCryptDestroyKey(mImpl->KeyHandle);
        mImpl->KeyHandle = nullptr;
    }
    // FIXME: no error logged if blob is malformed, just returns false
    NTSTATUS Status = BCryptImportKeyPair(
        mImpl->AlgHandle, nullptr, L"RSAPUBLICBLOB",
        &mImpl->KeyHandle,
        const_cast<PUCHAR>(KeyBlob.data()), static_cast<ULONG>(KeyBlob.size()), 0);
    return NT_SUCCESS(Status);
}

bool RsaSigner::ImportPrivateKey(const Common::ByteArray& KeyBlob) {
    if (mImpl->KeyHandle) {
        BCryptDestroyKey(mImpl->KeyHandle);
        mImpl->KeyHandle = nullptr;
    }
    NTSTATUS Status = BCryptImportKeyPair(
        mImpl->AlgHandle, nullptr, L"RSAFULLPRIVATEBLOB",
        &mImpl->KeyHandle,
        const_cast<PUCHAR>(KeyBlob.data()), static_cast<ULONG>(KeyBlob.size()), 0);
    return NT_SUCCESS(Status);
}

Common::ByteArray RsaSigner::Sign(const Common::ByteArray& Data) {
    // expects caller to have pre-hashed the data, we just sign whatever we're given
    ULONG ResultSize = 0;
    BCryptSignHash(mImpl->KeyHandle, nullptr, const_cast<PUCHAR>(Data.data()),
                   static_cast<ULONG>(Data.size()), nullptr, 0, &ResultSize, 0);
    Common::ByteArray Result(ResultSize);
    BCryptSignHash(mImpl->KeyHandle, nullptr, const_cast<PUCHAR>(Data.data()),
                   static_cast<ULONG>(Data.size()), Result.data(),
                   static_cast<ULONG>(Result.size()), &ResultSize, 0);
    return Result;
}

bool RsaSigner::Verify(const Common::ByteArray& Data, const Common::ByteArray& Signature) {
    NTSTATUS Status = BCryptVerifySignature(
        mImpl->KeyHandle, nullptr, const_cast<PUCHAR>(Data.data()),
        static_cast<ULONG>(Data.size()), const_cast<PUCHAR>(Signature.data()),
        static_cast<ULONG>(Signature.size()), 0);
    return NT_SUCCESS(Status);
}

Common::ByteArray RsaSigner::GetPublicKey() const {
    ULONG ResultSize = 0;
    BCryptExportKey(mImpl->KeyHandle, nullptr, L"RSAPUBLICBLOB",
                    nullptr, 0, &ResultSize, 0);
    Common::ByteArray Result(ResultSize);
    BCryptExportKey(mImpl->KeyHandle, nullptr, L"RSAPUBLICBLOB",
                    Result.data(), ResultSize, &ResultSize, 0);
    return Result;
}

} // namespace Uues::Core::Crypto