#include "GuidGenerator.hpp"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <array>

#ifdef _WIN32
#include <objbase.h>
#pragma comment(lib, "ole32.lib")
#endif

namespace Uues::Core::Common {

Guid GuidGenerator::Create() {
    Guid Result{};
#ifdef _WIN32
    GUID WinGuid;
    if (CoCreateGuid(&WinGuid) == S_OK) {
        std::memcpy(Result.data(), &WinGuid, sizeof(GUID));
    }
    // TODO: fallback to manual UUID v4 generation if CoCreateGuid fails
#endif
    return Result;
}

String GuidGenerator::CreateString() {
    return ToString(Create());
}

String GuidGenerator::ToString(const Guid& G) {
    std::ostringstream Oss;
    Oss << std::hex << std::setfill('0')
        << std::setw(2);
    for (size_t I = 0; I < G.size(); ++I) {
        Oss << std::setw(2) << static_cast<int>(G[I]);
        if (I == 3 || I == 5 || I == 7 || I == 9) Oss << '-';
    }
    return Oss.str();
}

Guid GuidGenerator::FromString(const std::string& Str) {
    Guid Result{};
    std::string Clean;
    for (char C : Str) {
        if (C != '-' && C != '{' && C != '}') Clean += C;
    }
    if (Clean.length() != 32) return Result;
    for (size_t I = 0; I < 16; ++I) {
        std::string ByteStr = Clean.substr(I * 2, 2);
        Result[I] = static_cast<Byte>(std::stoul(ByteStr, nullptr, 16));
    }
    return Result;
}

bool GuidGenerator::IsValid(const std::string& Str) {
    std::string Clean;
    for (char C : Str) {
        if (C != '-' && C != '{' && C != '}') Clean += C;
    }
    if (Clean.length() != 32) return false;
    return std::all_of(Clean.begin(), Clean.end(), [](char C) {
        return std::isxdigit(static_cast<unsigned char>(C));
    });
}

} // namespace Uues::Core::Common