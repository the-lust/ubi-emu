#include "R1FriendHandler.hpp"

namespace Uues::EmuR1 {
using namespace Uues::Core;

// offline mode - no friends
unsigned int R1FriendHandler::GetFriendCount() {
    return 0;
}

Common::StringList R1FriendHandler::GetFriendList() {
    return {}; // empty list
}

} // namespace Uues::EmuR1
