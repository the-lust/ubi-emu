#include "OrbitSaveHandler.hpp"
#include "../Core/Log/Logger.hpp"
#include "../Core/Storage/SaveManager.hpp"
#include <cstring>

namespace Uues::EmuOrbit {
using namespace Uues::Core;

bool OrbitSaveHandler::Get(void* Buffer, unsigned int* BufferSize) {
    if (!BufferSize) {
        Log::Logger::GetInstance().Warning("[OrbitSave] Get called with null BufferSize");
        return false;
    }
    Common::ByteArray Data;
    if (!Storage::SaveManager::GetInstance().LoadFile("orbit_save", Data)) {
        *BufferSize = 0;
        return Buffer == nullptr;
    }
    unsigned int CopySize = std::min(*BufferSize, static_cast<unsigned int>(Data.size()));
    if (Buffer && CopySize > 0) {
        std::memcpy(Buffer, Data.data(), CopySize);
    }
    *BufferSize = static_cast<unsigned int>(Data.size());
    Log::Logger::GetInstance().Info("[OrbitSave] Loaded save (" + std::to_string(Data.size()) + " bytes)");
    return true;
}

bool OrbitSaveHandler::Set(const void* Buffer, unsigned int BufferSize) {
    if (!Buffer || BufferSize == 0) {
        Log::Logger::GetInstance().Warning("[OrbitSave] Set called with empty data");
        return false;
    }
    Common::ByteArray Data(static_cast<const Common::Byte*>(Buffer), static_cast<const Common::Byte*>(Buffer) + BufferSize);
    bool Ok = Storage::SaveManager::GetInstance().SaveFile("orbit_save", Data);
    if (Ok) {
        Log::Logger::GetInstance().Info("[OrbitSave] Saved " + std::to_string(BufferSize) + " bytes");
    }
    return Ok;
}

} // namespace Uues::EmuOrbit