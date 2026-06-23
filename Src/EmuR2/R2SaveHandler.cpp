#include "R2SaveHandler.hpp"
#include "../Core/Storage/SaveManager.hpp"
#include <cstring>
#include <algorithm>

namespace Uues::EmuR2 {
using namespace Uues::Core;

bool R2SaveHandler::GetSaveGame(const Common::String& SaveName, void* Buffer, unsigned int* BufferSize) {
    if (!BufferSize) return false;
    Common::ByteArray Data;
    if (!Storage::SaveManager::GetInstance().LoadFile(SaveName, Data)) {
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

bool R2SaveHandler::SetSaveGame(const Common::String& SaveName, const void* Buffer, unsigned int BufferSize) {
    if (!Buffer || BufferSize == 0) return false;
    Common::ByteArray Data(static_cast<const Common::Byte*>(Buffer),
                           static_cast<const Common::Byte*>(Buffer) + BufferSize);
    return Storage::SaveManager::GetInstance().SaveFile(SaveName, Data);
}

} // namespace Uues::EmuR2