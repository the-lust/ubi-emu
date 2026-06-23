#pragma once

#include "Types.hpp"
#include <string>

namespace Uues::Core::Common {

class GuidGenerator {
public:
    static Guid Create();
    static String CreateString();
    static String ToString(const Guid& Guid);
    static Guid FromString(const std::string& Str);
    static bool IsValid(const std::string& Str);

private:
    GuidGenerator() = delete;
};

} // namespace Uues::Core::Common