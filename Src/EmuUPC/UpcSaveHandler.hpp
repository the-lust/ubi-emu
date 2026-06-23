#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuUPC {

class UpcSaveHandler {
public:
    // max save size per ubi spec is 256KB
    static const unsigned int MAX_SAVE_SIZE = 256 * 1024;

    static bool GetSaveGame(const Core::Common::String& SaveName, void* Buffer, unsigned int* BufferSize);
    static bool SetSaveGame(const Core::Common::String& SaveName, const void* Buffer, unsigned int BufferSize);
};

} // namespace Uues::EmuUPC