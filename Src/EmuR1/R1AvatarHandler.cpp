#include "R1AvatarHandler.hpp"
#include "../Core/Common/GuidGenerator.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuR1 {
using namespace Uues::Core;

static Common::String sGeneratedAvatarId;

Common::String R1AvatarHandler::GetAvatarIdForCurrentUser() {
    if (sGeneratedAvatarId.empty()) {
        sGeneratedAvatarId = Common::GuidGenerator::Generate().ToString();
        Log::Logger::GetInstance().Debug("[R1Avatar] Generated avatar ID: " + sGeneratedAvatarId);
    }
    return sGeneratedAvatarId;
}

bool R1AvatarHandler::GetAvatarBitmap(const Common::String& AvatarId, Common::ByteArray& OutBitmap) {
    Log::Logger::GetInstance().Warning("[R1Avatar] Bitmap retrieval not implemented, returning default");
    return false;
}

} // namespace Uues::EmuR1