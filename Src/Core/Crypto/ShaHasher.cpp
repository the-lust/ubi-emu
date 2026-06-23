#include "ShaHasher.hpp"
#include "../Common/BufferUtils.hpp"
#include <windows.h>
#include <bcrypt.h>

#pragma comment(lib, "bcrypt.lib")

namespace Uues::Core::Crypto {

Common::ByteArray ShaHasher::Sha256(const Common::ByteArray& Data) {
    BCRYPT_ALG_HANDLE AlgHandle = nullptr;
    BCryptOpenAlgorithmProvider(&AlgHandle, BCRYPT_SHA256_ALGORITHM, nullptr, 0);

    Dword hash_len = 0;
    Dword ResultSize = 0;
    BCryptGetProperty(AlgHandle, BCRYPT_HASH_LENGTH,
                      reinterpret_cast<PUCHAR>(&hash_len), sizeof(Dword), &ResultSize, 0);

    Common::ByteArray Result(hash_len);
    BCryptHash(AlgHandle, const_cast<PUCHAR>(Data.data()), static_cast<ULONG>(Data.size()),
               Result.data(), static_cast<ULONG>(Result.size()));

    BCryptCloseAlgorithmProvider(AlgHandle, 0);
    return Result;
}

Common::ByteArray ShaHasher::Sha1(const Common::ByteArray& Data) {
    BCRYPT_ALG_HANDLE AlgHandle = nullptr;
    BCryptOpenAlgorithmProvider(&AlgHandle, BCRYPT_SHA1_ALGORITHM, nullptr, 0);

    Dword HashSize = 0;
    Dword ResultSize = 0;
    BCryptGetProperty(AlgHandle, BCRYPT_HASH_LENGTH,
                      reinterpret_cast<PUCHAR>(&HashSize), sizeof(Dword), &ResultSize, 0);

    Common::ByteArray Result(HashSize);
    // SHA-1 is deprecated but some legacy services still use it *shrug*
    BCryptHash(AlgHandle, const_cast<PUCHAR>(Data.data()), static_cast<ULONG>(Data.size()),
               Result.data(), static_cast<ULONG>(Result.size()));

    BCryptCloseAlgorithmProvider(AlgHandle, 0);
    return Result;
}

Common::String ShaHasher::Sha256Hex(const Common::ByteArray& Data) {
    auto Hash = Sha256(Data);
    return Common::BufferUtils::ToHex(Hash);
}

} // namespace Uues::Core::Crypto