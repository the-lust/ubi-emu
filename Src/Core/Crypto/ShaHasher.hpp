#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Crypto {

class ShaHasher {
public:
    static Common::ByteArray Sha256(const Common::ByteArray& Data);
    static Common::ByteArray Sha1(const Common::ByteArray& Data);
    static Common::String Sha256Hex(const Common::ByteArray& Data);

private:
    ShaHasher() = delete;
};

} // namespace Uues::Core::Crypto