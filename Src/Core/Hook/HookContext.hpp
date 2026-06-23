#pragma once

#include "../Common/Types.hpp"

namespace Uues::Core::Hook {

struct HookContext {
    void* TargetFunction;
    void* DetourFunction;
    void* OriginalFunction;
    Common::String FunctionName;
    Common::String ModuleName;
    bool IsEnabled;
};

} // namespace Uues::Core::Hook