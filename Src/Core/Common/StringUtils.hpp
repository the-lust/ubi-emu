#pragma once

#include "Types.hpp"
#include <vector>
#include <string_view>

namespace Uues::Core::Common {

class StringUtils {
public:
    static String Trim(const String& Str);
    static String TrimLeft(const String& Str);
    static String TrimRight(const String& Str);
    static String ToLower(const String& Str);
    static String ToUpper(const String& Str);
    static bool EqualsIgnoreCase(const String& A, const String& B);
    static bool StartsWith(const String& Str, const String& Prefix);
    static bool EndsWith(const String& Str, const String& Suffix);
    static StringList Split(const String& Str, char Delimiter);
    static StringList Split(const String& Str, const String& Delimiter);
    static String Join(const StringList& Parts, const String& Joiner);
    static String Replace(const String& Str, const String& From, const String& To);
    static String Format(const char* Format, ...);
    static WString ToWide(const String& Utf8);
    static String FromWide(const WString& Wide);
    static bool TryParseInt(const String& Str, int& Out);
    static bool TryParseUint(const String& Str, unsigned int& Out);

private:
    StringUtils() = delete;
};

} // namespace Uues::Core::Common