#include "UpcSaveHandler.hpp"
#include "../Core/Storage/SaveManager.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstring>
#include <algorithm>

namespace Uues::EmuUPC {
using namespace Uues::Core;

bool UpcSaveHandler::GetSaveGame(const Common::String& SaveName, void* Buffer, unsigned int* BufferSize) {
    if (!BufferSize) return false;
    Common::ByteArray Data;
    if (!Storage::SaveManager::GetInstance().LoadFile(SaveName, Data)) {
        Log::Logger::GetInstance().Warning("[UPCSave] Failed to load save: " + SaveName);
        *BufferSize = 0;
        return Buffer == nullptr;
    }
    unsigned int CopySize = std::min(*BufferSize, static_cast<unsigned int>(Data.size()));
    if (Buffer && CopySize > 0) {
        std::memcpy(Buffer, Data.data(), CopySize);
    }
    *BufferSize = static_cast<unsigned int>(Data.size());
    return true;
}

bool UpcSaveHandler::SetSaveGame(const Common::String& SaveName, const void* Buffer, unsigned int BufferSize) {
    if (!Buffer || BufferSize == 0) {
        Log::Logger::GetInstance().Warning("[UPCSave] Empty save data for: " + SaveName);
        return false;
    }
    Common::ByteArray Data(static_cast<const Common::Byte*>(Buffer),
                           static_cast<const Common::Byte*>(Buffer) + BufferSize);
    bool Ok = Storage::SaveManager::GetInstance().SaveFile(SaveName, Data);
    if (!Ok) {
        Log::Logger::GetInstance().Error("[UPCSave] Failed to save: " + SaveName);
    }
    return Ok;
}

} // namespace Uues::EmuUPC