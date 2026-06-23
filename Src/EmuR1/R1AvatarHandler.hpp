#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuR1 {

class R1AvatarHandler {
public:
    static Core::Common::String GetAvatarIdForCurrentUser();
    static bool GetAvatarBitmap(const Core::Common::String& AvatarId, Common::ByteArray& OutBitmap);

private:
    R1AvatarHandler() = delete; // purely static
};

} // namespace Uues::EmuR1