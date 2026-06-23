#include "R1SaveHandler.hpp"
#include "../Core/Storage/SaveManager.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuR1 {
using namespace Uues::Core;

bool R1SaveHandler::GetSaveGame(const Common::String& SaveName, Common::ByteArray& OutData) {
    if (!Storage::SaveManager::GetInstance().LoadFile(SaveName, OutData)) {
        Log::Logger::GetInstance().Warning("[R1Save] Save not found: " + SaveName);
        return false;
    }
    Log::Logger::GetInstance().Info("[R1Save] Loaded save: " + SaveName + " (" + std::to_string(OutData.size()) + " bytes)");
    return true;
}

bool R1SaveHandler::SetSaveGame(const Common::String& SaveName, const Common::ByteArray& Data) {
    bool Ok = Storage::SaveManager::GetInstance().SaveFile(SaveName, Data);
    if (Ok) {
        Log::Logger::GetInstance().Info("[R1Save] Saved: " + SaveName + " (" + std::to_string(Data.size()) + " bytes)");
    }
    return Ok;
}

} // namespace Uues::EmuR1