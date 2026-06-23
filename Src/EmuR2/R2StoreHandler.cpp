#include "R2StoreHandler.hpp"
#include "../Core/Log/Logger.hpp"
#include "../Core/Storage/DlcManager.hpp"
#include <cstring>

namespace Uues::EmuR2 {
using namespace Uues::Core;

bool R2StoreHandler::GetStoreItems(char* Buffer, unsigned int BufferSize) {
    auto& logger = Log::Logger::GetInstance();
    logger.Info("[R2Store] GetStoreItems called (BufferSize=" + std::to_string(BufferSize) + ")");

    if (!Buffer || BufferSize == 0) {
        return BufferSize == 0;
    }

    auto DlcStrings = Storage::DlcManager::GetInstance().GetAllDlcs();
    Common::String Response = "[";
    for (size_t i = 0; i < DlcStrings.size(); ++i) {
        if (i > 0) Response += ",";
        Response += "{\"id\":" + DlcStrings[i] + ",\"owned\":true}";
    }
    Response += "]";

    strncpy_s(Buffer, BufferSize, Response.c_str(), BufferSize - 1);
    logger.Info("[R2Store] Returning " + std::to_string(DlcStrings.size()) + " store items");
    return true;
}

} // namespace Uues::EmuR2