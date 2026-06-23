#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Crypto {

class RsaSigner {
public:
    RsaSigner();
    ~RsaSigner();

    bool ImportPublicKey(const Common::ByteArray& KeyBlob);
    bool ImportPrivateKey(const Common::ByteArray& KeyBlob);
    Common::ByteArray Sign(const Common::ByteArray& Data);
    bool Verify(const Common::ByteArray& Data, const Common::ByteArray& Signature);
    Common::ByteArray GetPublicKey() const;

private:
    class Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace Uues::Core::Crypto