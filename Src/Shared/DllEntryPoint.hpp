#pragma once

#include <windows.h>

namespace Uues::Shared {

class DllEntryPoint {
public:
    static HINSTANCE GetInstance();
    static void SetInstance(HINSTANCE Instance);

private:
    static HINSTANCE mInstance;
};

} // namespace Uues::Shared