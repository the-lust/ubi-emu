#pragma once

#include "../Core/Common/Types.hpp"

namespace Uues::EmuR1 {

class R1UserHandler {
public:
    static Core::Common::String GetUsername();
    static Core::Common::String GetUsernameUtf8();
    static Core::Common::String GetEmail();
    static Core::Common::String GetPassword();
    static Core::Common::String GetPasswordUtf8();
    static Core::Common::String GetCredentials();

private:
    R1UserHandler() = delete; // static helper
};

} // namespace Uues::EmuR1