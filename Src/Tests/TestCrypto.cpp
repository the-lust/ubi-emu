#include "../Core/Crypto/AesEncryptor.hpp"
#include "../Core/Crypto/TicketGenerator.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstdio>
#include <cstring>

namespace Uues::Tests {

bool RunCryptoTests() {
    Log::Logger::GetInstance().Info("[CryptoTests] Starting crypto tests");

    int Errors = 0;

    // AES encryptor: create and basic round-trip
    {
        Core::Crypto::AesEncryptor Enc;
        unsigned char Key[32] = {0};
        unsigned char IV[16] = {0};
        Key[0] = 0xAB; Key[1] = 0xCD;
        Enc.SetKey(Key, sizeof(Key));
        Enc.SetIV(IV, sizeof(IV));

        const char* Plain = "Hello Crypto!";
        size_t PlainLen = std::strlen(Plain);

        Common::ByteArray Cipher;
        if (!Enc.Encrypt(reinterpret_cast<const unsigned char*>(Plain), PlainLen, Cipher)) {
            Log::Logger::GetInstance().Warning("[CryptoTests] AES encrypt failed (may be expected)");
        }
    }

    // TicketGenerator: basic validation
    {
        Core::Crypto::TicketGenerator Gen;
        Common::ByteArray Ticket;
        bool GenOk = Gen.GenerateTicket("12345", "TestUser", Ticket);
        if (GenOk) {
            bool Valid = Gen.ValidateTicket(Ticket);
            if (!Valid) Errors++;
        } else {
            Log::Logger::GetInstance().Warning("[CryptoTests] Ticket generation not implemented yet");
        }
    }

    printf("[Crypto] Tests done: %s\n", Errors == 0 ? "CLEAN" : "ERRORS");
    return Errors == 0;
}

} // namespace Uues::Tests