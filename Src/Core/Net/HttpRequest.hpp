#pragma once

#include "../Common/Types.hpp"
#include <unordered_map>

namespace Uues::Core::Net {

class HttpRequest {
public:
    HttpRequest();
    ~HttpRequest();

    bool Get(const Common::String& Url, Common::String& OutResponse, int TimeoutMs = 5000);
    bool Post(const Common::String& Url, const Common::String& Body,
              Common::String& OutResponse, int TimeoutMs = 5000);
    bool PostJson(const Common::String& Url, const Common::String& JsonBody,
                  Common::String& OutResponse, int TimeoutMs = 5000);

    void SetHeader(const Common::String& Name, const Common::String& Value);
    void SetUserAgent(const Common::String& Agent);

private:
    class Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace Uues::Core::Net