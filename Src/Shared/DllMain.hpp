#pragma once

#include <windows.h>

namespace Uues::Shared {

class DllMain {
public:
    static bool OnProcessAttach(HINSTANCE Instance);
    static bool OnProcessDetach(HINSTANCE Instance);
    static bool OnThreadAttach(HINSTANCE Instance);
    static bool OnThreadDetach(HINSTANCE Instance);

private:
    DllMain() = delete;
};

} // namespace Uues::Shared