#pragma once

#include "../Common/Types.hpp"
#include <unordered_map>

namespace Uues::Core::Proto {

class DemuxMessage {
public:
    DemuxMessage();
    ~DemuxMessage();

    void SetRequestId(uint32_t Id);
    void SetServiceId(uint32_t Id);
    void SetMethodId(uint32_t Id);
    void SetPayload(const Common::ByteArray& Payload);
    void SetHeader(const Common::String& Key, const Common::String& Value);

    uint32_t GetRequestId() const;
    uint32_t GetServiceId() const;
    uint32_t GetMethodId() const;
    Common::ByteArray GetPayload() const;
    Common::String GetHeader(const Common::String& Key) const;

    Common::ByteArray Serialize() const;
    bool Deserialize(const Common::ByteArray& Data);

private:
    uint32_t mRequestId = 0;
    uint32_t mServiceId = 0;
    uint32_t mMethodId = 0;
    Common::ByteArray mPayload;
    std::unordered_map<Common::String, Common::String> mHeaders;
};

} // namespace Uues::Core::Proto