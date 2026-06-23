#pragma once

#include "../Common/Types.hpp"
#include <unordered_map>

namespace Uues::Core::Net {

class HttpResponse {
public:
    HttpResponse();
    ~HttpResponse();

    bool Parse(const Common::String& RawResponse);
    int GetStatusCode() const;
    Common::String GetStatusText() const;
    Common::String GetHeader(const Common::String& Name) const;
    Common::String GetBody() const;

private:
    int mStatusCode = 0;
    Common::String mStatusText;
    Common::String mBody;
    std::unordered_map<Common::String, Common::String> mHeaders;
};

} // namespace Uues::Core::Net