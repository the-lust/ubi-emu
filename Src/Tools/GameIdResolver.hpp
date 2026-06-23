#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::Tools {

class GameIdResolver {
public:
    static int ResolveAppId(const Core::Common::String& GameName);
    static Core::Common::String ResolveGameName(int AppId);
};

} // namespace Uues::Tools