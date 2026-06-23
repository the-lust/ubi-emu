#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuR1 {

class R1SaveHandler {
public:
    static bool GetSaveGame(const Core::Common::String& SaveName, Uues::Core::Common::ByteArray& OutData);
    static bool SetSaveGame(const Core::Common::String& SaveName, const Uues::Core::Common::ByteArray& Data);

private:
    R1SaveHandler() = delete; // static class
};

} // namespace Uues::EmuR1