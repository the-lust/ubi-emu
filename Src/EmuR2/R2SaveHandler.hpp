#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuR2 {

class R2SaveHandler {
public:
    static bool GetSaveGame(const Core::Common::String& SaveName, void* Buffer, unsigned int* BufferSize);
    static bool SetSaveGame(const Core::Common::String& SaveName, const void* Buffer, unsigned int BufferSize); // Buffer may be null
};

} // namespace Uues::EmuR2