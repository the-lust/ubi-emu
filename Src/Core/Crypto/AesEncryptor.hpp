#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Crypto {

class AesEncryptor {
public:
    AesEncryptor();
    ~AesEncryptor();

    bool SetKey(const Common::ByteArray& Key);
    bool SetIv(const Common::ByteArray& Iv);
    Common::ByteArray Encrypt(const Common::ByteArray& Data);
    Common::ByteArray Decrypt(const Common::ByteArray& Data);
    Common::ByteArray EncryptCbc(const Common::ByteArray& Data);
    Common::ByteArray DecryptCbc(const Common::ByteArray& Data);

private:
    class Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace Uues::Core::Crypto