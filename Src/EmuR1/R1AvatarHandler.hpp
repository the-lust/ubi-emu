#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuR1 {

class R1AvatarHandler {
public:
    static Uues::Core::Common::String GetAvatarIdForCurrentUser();
    static bool GetAvatarBitmap(const Uues::Core::Common::String& AvatarId, Uues::Core::Common::ByteArray& OutBitmap);

private:
    R1AvatarHandler() = delete; // purely static
};

} // namespace Uues::EmuR1