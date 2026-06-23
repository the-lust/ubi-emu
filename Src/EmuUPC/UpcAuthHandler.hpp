#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuUPC {

class UpcAuthHandler {
public:
    static Core::Common::String GetUsername();
    static Core::Common::String GetEmail();
    static bool Authenticate(const Core::Common::String& Token); // token is ignored for now
};

} // namespace Uues::EmuUPC