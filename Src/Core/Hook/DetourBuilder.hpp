#pragma once

#include "../Common/Types.hpp"
#include <functional>

namespace Uues::Core::Hook {

class DetourBuilder {
public:
    DetourBuilder();
    ~DetourBuilder();

    void* BuildDetour(void* TargetFunction, const Common::ByteArray& DetourCode);
    bool IsValidDetour(void* Address, size_t MinLength = 5) const;
    size_t GetNecessaryLength(void* TargetFunction, size_t MinLength = 5) const;

private:
    Common::ByteArray mDetourCode;
};

} // namespace Uues::Core::Hook