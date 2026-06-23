#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuR1 {

class R1FriendHandler {
public:
    static unsigned int GetFriendCount();
    static Core::Common::StringList GetFriendList();

private:
    R1FriendHandler() = delete; // static only
};

} // namespace Uues::EmuR1