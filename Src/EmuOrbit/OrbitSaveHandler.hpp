#pragma once

namespace Uues::EmuOrbit {

class OrbitSaveHandler {
public:
    static bool Get(void* Buffer, unsigned int* BufferSize);
    static bool Set(const void* Buffer, unsigned int BufferSize);
};

} // namespace Uues::EmuOrbit