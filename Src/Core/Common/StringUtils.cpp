#include "StringUtils.hpp"
#include <algorithm>
#include <sstream>
#include <cstdarg>
#include <cwchar>

namespace Uues::Core::Common {

String StringUtils::Trim(const String& Str) {
    // NOTE: doesn't trim \0 chars embedded in the middle, should it?
    return TrimRight(TrimLeft(Str));
}

String StringUtils::TrimLeft(const String& Str) {
    auto Start = std::find_if_not(Str.begin(), Str.end(), [](unsigned char C) {
        return std::isspace(C);
    });
    return {Start, Str.end()};
}

String StringUtils::TrimRight(const String& Str) {
    auto End = std::find_if_not(Str.rbegin(), Str.rend(), [](unsigned char C) {
        return std::isspace(C);
    }).base();
    return {Str.begin(), End};
}

String StringUtils::ToLower(const String& Str) {
    String Result = Str;
    std::transform(Result.begin(), Result.end(), Result.begin(), [](unsigned char C) {
        return static_cast<char>(std::tolower(C));
    });
    return Result;
}

String StringUtils::ToUpper(const String& Str) {
    String Result = Str;
    std::transform(Result.begin(), Result.end(), Result.begin(), [](unsigned char C) {
        return static_cast<char>(std::toupper(C));
    });
    return Result;
}

bool StringUtils::EqualsIgnoreCase(const String& A, const String& B) {
    return ToLower(A) == ToLower(B);
}

bool StringUtils::StartsWith(const String& Str, const String& Prefix) {
    // HACK: case-sensitive always, no overload for case-insensitive
    return Str.size() >= Prefix.size() && Str.compare(0, Prefix.size(), Prefix) == 0;
}

bool StringUtils::EndsWith(const String& Str, const String& Suffix) {
    return Str.size() >= Suffix.size() && Str.compare(Str.size() - Suffix.size(), Suffix.size(), Suffix) == 0;
}

StringList StringUtils::Split(const String& Str, char Delimiter) {
    StringList Result;
    std::istringstream Stream(Str);
    String Token;
    // TODO: what if Delimiter is '\0'? getline will behave weirdly
    while (std::getline(Stream, Token, Delimiter)) {
        Result.push_back(Token);
    }
    return Result;
}

StringList StringUtils::Split(const String& Str, const String& Delimiter) {
    StringList Result;
    size_t Start = 0, End;
    while ((End = Str.find(Delimiter, Start)) != String::npos) {
        Result.push_back(Str.substr(Start, End - Start));
        Start = End + Delimiter.length();
    }
    Result.push_back(Str.substr(Start));
    return Result;
}

String StringUtils::Join(const StringList& Parts, const String& Joiner) {
    String Result;
    for (size_t I = 0; I < Parts.size(); ++I) {
        if (I > 0) Result += Joiner;
        Result += Parts[I];
    }
    return Result;
}

String StringUtils::Replace(const String& Str, const String& From, const String& To) {
    String Result = Str;
    size_t Pos = 0;
    while ((Pos = Result.find(From, Pos)) != String::npos) {
        Result.replace(Pos, From.length(), To);
        Pos += To.length();
    }
    return Result;
}

String StringUtils::Format(const char* Fmt, ...) {
    va_list Args;
    va_start(Args, Fmt);
    va_list ArgsCopy;
    va_copy(ArgsCopy, Args);
    int Size = std::vsnprintf(nullptr, 0, Fmt, ArgsCopy);
    va_end(ArgsCopy);
    if (Size < 0) { va_end(Args); return {}; }
    String Result(Size + 1, '\0');
    std::vsnprintf(Result.data(), Size + 1, Fmt, Args);
    va_end(Args);
    Result.resize(Size);
    return Result;
}

WString StringUtils::ToWide(const String& Utf8) {
    if (Utf8.empty()) return {};
    int Size = MultiByteToWideChar(CP_UTF8, 0, Utf8.c_str(), -1, nullptr, 0);
    WString Result(Size, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, Utf8.c_str(), -1, Result.data(), Size);
    Result.resize(Size - 1);
    return Result;
}

String StringUtils::FromWide(const WString& Wide) {
    if (Wide.empty()) return {};
    int Size = WideCharToMultiByte(CP_UTF8, 0, Wide.c_str(), -1, nullptr, 0, nullptr, nullptr);
    String Result(Size, '\0');
    WideCharToMultiByte(CP_UTF8, 0, Wide.c_str(), -1, Result.data(), Size, nullptr, nullptr);
    Result.resize(Size - 1);
    return Result;
}

bool StringUtils::TryParseInt(const String& Str, int& Out) {
    try {
        size_t Pos;
        Out = std::stoi(Str, &Pos);
        return Pos == Str.length();
    } catch (...) {
        return false;
    }
}

bool StringUtils::TryParseUint(const String& Str, unsigned int& Out) {
    try {
        size_t Pos;
        Out = std::stoul(Str, &Pos);
        return Pos == Str.length();
    } catch (...) {
        return false;
    }
}

} // namespace Uues::Core::Common