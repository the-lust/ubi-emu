#include "HttpResponse.hpp"
#include "../Common/StringUtils.hpp"
#include <sstream>

namespace Uues::Core::Net {

HttpResponse::HttpResponse() {}
HttpResponse::~HttpResponse() = default;

bool HttpResponse::Parse(const Common::String& RawResponse) {
    // FIXME: this doesn't handle HTTP/2 responses or chunked transfer encoding
    auto HeaderEnd = RawResponse.find("\r\n\r\n");
    if (HeaderEnd == Common::String::npos) return false;

    auto HeaderPart = RawResponse.substr(0, HeaderEnd);
    mBody = RawResponse.substr(HeaderEnd + 4);

    auto Lines = Common::StringUtils::Split(HeaderPart, '\n');
    if (Lines.empty()) return false;

    auto StatusLine = Common::StringUtils::Trim(Lines[0]);
    auto FirstSpace = StatusLine.find(' ');
    auto SecondSpace = StatusLine.find(' ', FirstSpace + 1);
    if (FirstSpace == Common::String::npos) return false;

    auto StatusCodeStr = StatusLine.substr(FirstSpace + 1, SecondSpace - FirstSpace - 1);
    mStatusCode = std::stoi(StatusCodeStr);
    mStatusText = (SecondSpace != Common::String::npos) ? StatusLine.substr(SecondSpace + 1) : "";

    for (size_t I = 1; I < Lines.size(); ++I) {
        auto Line = Common::StringUtils::Trim(Lines[I]);
        auto Colon = Line.find(':');
        if (Colon != Common::String::npos) {
            auto Name = Common::StringUtils::Trim(Line.substr(0, Colon));
            auto Value = Common::StringUtils::Trim(Line.substr(Colon + 1));
            mHeaders[Common::StringUtils::ToLower(Name)] = Value;
        }
    }

    return true;
}

int HttpResponse::GetStatusCode() const { return mStatusCode; }
Common::String HttpResponse::GetStatusText() const { return mStatusText; }

Common::String HttpResponse::GetHeader(const Common::String& Name) const {
    auto It = mHeaders.find(Common::StringUtils::ToLower(Name));
    return (It != mHeaders.end()) ? It->second : "";
}

Common::String HttpResponse::GetBody() const { return mBody; }

} // namespace Uues::Core::Net