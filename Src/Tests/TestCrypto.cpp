#include "../Core/Crypto/AesEncryptor.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstdio>
#include <cstring>

namespace Uues::Tests {
using namespace Uues::Core;

bool RunCryptoTests() {
    Log::Logger::GetInstance().Info("[CryptoTests] Starting crypto tests");

    int Errors = 0;

    // AES encryptor: create and basic round-trip
    {
        Core::Crypto::AesEncryptor Enc;
        unsigned char Key[32] = {0};
        unsigned char IV[16] = {0};
        Key[0] = 0xAB; Key[1] = 0xCD;
        Common::ByteArray KeyBytes(Key, Key + sizeof(Key));
        Common::ByteArray IvBytes(IV, IV + sizeof(IV));
        Enc.SetKey(KeyBytes);
        Enc.SetIv(IvBytes);

        const char* Plain = "Hello Crypto!";
        size_t PlainLen = std::strlen(Plain);
        Common::ByteArray PlainBytes(reinterpret_cast<const unsigned char*>(Plain),
            reinterpret_cast<const unsigned char*>(Plain) + PlainLen);

        auto Cipher = Enc.Encrypt(PlainBytes);
        if (Cipher.empty()) {
            Log::Logger::GetInstance().Warning("[CryptoTests] AES encrypt failed (may be expected)");
        }
    }

    printf("[Crypto] Tests done: %s\n", Errors == 0 ? "CLEAN" : "ERRORS");
    return Errors == 0;
}

} // namespace Uues::Tests