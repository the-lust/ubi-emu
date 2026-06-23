#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuR2 {

class R2UserHandler {
public:
    static Core::Common::String GetUsername();
    static Core::Common::String GetEmail(); // may return empty if not set
};

} // namespace Uues::EmuR2