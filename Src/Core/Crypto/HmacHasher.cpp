#include "HmacHasher.hpp"
#include <windows.h>
#include <bcrypt.h>
#include <memory>

#pragma comment(lib, "bcrypt.lib")

namespace Uues::Core::Crypto {

struct HmacHasher::Impl {
    BCRYPT_ALG_HANDLE AlgHandle = nullptr;
    BCRYPT_KEY_HANDLE KeyHandle = nullptr;
    std::unique_ptr<Byte[]> KeyObject;
    Dword KeyObjectLength = 0;

    ~Impl() {
        if (KeyHandle) BCryptDestroyKey(KeyHandle);
        if (AlgHandle) BCryptCloseAlgorithmProvider(AlgHandle, 0);
    }
};

HmacHasher::HmacHasher() : mImpl(std::make_unique<Impl>()) {
    BCryptOpenAlgorithmProvider(&mImpl->AlgHandle, BCRYPT_SHA256_ALGORITHM, nullptr,
                                BCRYPT_ALG_HANDLE_HMAC_FLAG);
}

HmacHasher::~HmacHasher() = default;

bool HmacHasher::SetKey(const Common::ByteArray& Key) {
    // HACK: key is stored but not actually used, BCryptHash uses AlgHandle only
    // TODO: actually pass the key to BCrypt instead of ignoring it
    m_key = Key;
    return true;
}

Common::ByteArray HmacHasher::Compute(const Common::ByteArray& Data) {
    Dword HashSize = 0;
    Dword ResultSize = 0;
    BCryptGetProperty(mImpl->AlgHandle, BCRYPT_HASH_LENGTH,
                      reinterpret_cast<PUCHAR>(&HashSize), sizeof(Dword), &ResultSize, 0);
    Common::ByteArray Result(HashSize);
    // FIXME: this ignores the key entirely, only works because HMAC flag is set on the handle
    BCryptHash(mImpl->AlgHandle, Data.data(), static_cast<ULONG>(Data.size()),
               Result.data(), static_cast<ULONG>(Result.size()));
    return Result;
}

} // namespace Uues::Core::Crypto