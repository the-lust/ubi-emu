#include "AesEncryptor.hpp"
#include <windows.h>
#include <bcrypt.h>
#include <stdexcept>
#include <memory>

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

#pragma comment(lib, "bcrypt.lib")

namespace Uues::Core::Crypto {

class AesEncryptor::Impl {
public:
    BCRYPT_ALG_HANDLE AlgHandle = nullptr;
    BCRYPT_KEY_HANDLE KeyHandle = nullptr;
    Common::ByteArray Key;
    Common::ByteArray Iv;
    Dword KeyObjectLength = 0;
    std::unique_ptr<Byte[]> KeyObject;

    ~Impl() {
        if (KeyHandle) BCryptDestroyKey(KeyHandle);
        if (AlgHandle) BCryptCloseAlgorithmProvider(AlgHandle, 0);
    }
};

AesEncryptor::AesEncryptor() : mImpl(std::make_unique<Impl>()) {
    BCryptOpenAlgorithmProvider(&mImpl->AlgHandle, BCRYPT_AES_ALGORITHM, nullptr, 0);
    BCryptGetProperty(mImpl->AlgHandle, BCRYPT_OBJECT_LENGTH,
                      reinterpret_cast<PUCHAR>(&mImpl->KeyObjectLength),
                      sizeof(Dword), nullptr, 0);
    mImpl->KeyObject = std::make_unique<Byte[]>(mImpl->KeyObjectLength);
}

AesEncryptor::~AesEncryptor() = default;

bool AesEncryptor::SetKey(const Common::ByteArray& Key) {
    mImpl->Key = Key;
    if (mImpl->KeyHandle) {
        BCryptDestroyKey(mImpl->KeyHandle);
        mImpl->KeyHandle = nullptr;
    }
    // NOTE: supports 128/192/256-bit keys, BCrypt handles the rest
    NTSTATUS Status = BCryptGenerateSymmetricKey(
        mImpl->AlgHandle, &mImpl->KeyHandle,
        mImpl->KeyObject.get(), mImpl->KeyObjectLength,
        const_cast<PUCHAR>(Key.data()), static_cast<ULONG>(Key.size()), 0);
    return NT_SUCCESS(Status);
}

bool AesEncryptor::SetIv(const Common::ByteArray& Iv) {
    mImpl->Iv = Iv;
    return true;
}

Common::ByteArray AesEncryptor::Encrypt(const Common::ByteArray& Data) {
    // TODO: ECB mode is insecure for repeated data, should default to CBC
    BCryptSetProperty(mImpl->AlgHandle, BCRYPT_CHAINING_MODE,
                      reinterpret_cast<PUCHAR>(const_cast<wchar_t*>(L"ECB")),
                      sizeof(L"ECB"), 0);
    ULONG ResultSize = 0;
    // query output size first (two-call pattern typical of BCrypt)
    BCryptEncrypt(mImpl->KeyHandle, const_cast<PUCHAR>(Data.data()),
                  static_cast<ULONG>(Data.size()), nullptr,
                  nullptr, 0, nullptr, 0, &ResultSize, 0);
    Common::ByteArray Result(ResultSize);
    BCryptEncrypt(mImpl->KeyHandle, const_cast<PUCHAR>(Data.data()),
                  static_cast<ULONG>(Data.size()), nullptr,
                  nullptr, 0, Result.data(), ResultSize, &ResultSize, 0);
    return Result;
}

Common::ByteArray AesEncryptor::Decrypt(const Common::ByteArray& Data) {
    BCryptSetProperty(mImpl->AlgHandle, BCRYPT_CHAINING_MODE,
                      reinterpret_cast<PUCHAR>(const_cast<wchar_t*>(L"ECB")),
                      sizeof(L"ECB"), 0);
    ULONG ResultSize = 0;
    BCryptDecrypt(mImpl->KeyHandle, const_cast<PUCHAR>(Data.data()),
                  static_cast<ULONG>(Data.size()), nullptr,
                  nullptr, 0, nullptr, 0, &ResultSize, 0);
    Common::ByteArray Result(ResultSize);
    BCryptDecrypt(mImpl->KeyHandle, const_cast<PUCHAR>(Data.data()),
                  static_cast<ULONG>(Data.size()), nullptr,
                  nullptr, 0, Result.data(), ResultSize, &ResultSize, 0);
    return Result;
}

Common::ByteArray AesEncryptor::EncryptCbc(const Common::ByteArray& Data) {
    BCryptSetProperty(mImpl->AlgHandle, BCRYPT_CHAINING_MODE,
                      reinterpret_cast<PUCHAR>(const_cast<wchar_t*>(L"CBC")),
                      sizeof(L"CBC"), 0);
    ULONG ResultSize = 0;
    BCryptEncrypt(mImpl->KeyHandle, const_cast<PUCHAR>(Data.data()),
                  static_cast<ULONG>(Data.size()), nullptr,
                  mImpl->Iv.data(), static_cast<ULONG>(mImpl->Iv.size()),
                  nullptr, 0, &ResultSize, 0);
    Common::ByteArray Result(ResultSize);
    BCryptEncrypt(mImpl->KeyHandle, const_cast<PUCHAR>(Data.data()),
                  static_cast<ULONG>(Data.size()), nullptr,
                  mImpl->Iv.data(), static_cast<ULONG>(mImpl->Iv.size()),
                  Result.data(), ResultSize, &ResultSize, 0);
    return Result;
}

Common::ByteArray AesEncryptor::DecryptCbc(const Common::ByteArray& Data) {
    BCryptSetProperty(mImpl->AlgHandle, BCRYPT_CHAINING_MODE,
                      reinterpret_cast<PUCHAR>(const_cast<wchar_t*>(L"CBC")),
                      sizeof(L"CBC"), 0);
    ULONG ResultSize = 0;
    BCryptDecrypt(mImpl->KeyHandle, const_cast<PUCHAR>(Data.data()),
                  static_cast<ULONG>(Data.size()), nullptr,
                  mImpl->Iv.data(), static_cast<ULONG>(mImpl->Iv.size()),
                  nullptr, 0, &ResultSize, 0);
    Common::ByteArray Result(ResultSize);
    BCryptDecrypt(mImpl->KeyHandle, const_cast<PUCHAR>(Data.data()),
                  static_cast<ULONG>(Data.size()), nullptr,
                  mImpl->Iv.data(), static_cast<ULONG>(mImpl->Iv.size()),
                  Result.data(), ResultSize, &ResultSize, 0);
    return Result;
}

} // namespace Uues::Core::Crypto