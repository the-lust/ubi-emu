#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Crypto {

class HmacHasher {
public:
    HmacHasher();
    ~HmacHasher();

    bool SetKey(const Common::ByteArray& Key);
    Common::ByteArray Compute(const Common::ByteArray& Data);

private:
    class Impl;
    std::unique_ptr<Impl> mImpl;
    Common::ByteArray m_key;
};

} // namespace Uues::Core::Crypto