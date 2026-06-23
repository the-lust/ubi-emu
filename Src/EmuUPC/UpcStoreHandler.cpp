#include "UpcStoreHandler.hpp"
#include "../Core/Log/Logger.hpp"
#include "../Core/Storage/DlcManager.hpp"
#include <cstring>

namespace Uues::EmuUPC {
using namespace Uues::Core;

bool UpcStoreHandler::GetItems(char* Buffer, unsigned int BufferSize) {
    Log::Logger::GetInstance().Info("[UPCStore] GetItems called");

    if (!Buffer || BufferSize == 0) {
        return BufferSize == 0;
    }

    auto DlcStrings = Storage::DlcManager::GetInstance().GetAllDlcs();
    Common::String Response = "[";
    for (size_t i = 0; i < DlcStrings.size(); ++i) {
        if (i > 0) Response += ",";
        Response += "{\"product_id\":" + DlcStrings[i] + ",\"owned\":true,\"type\":\"consumable\"}";
    }
    Response += "]";

    strncpy_s(Buffer, BufferSize, Response.c_str(), BufferSize - 1);
    Log::Logger::GetInstance().Info("[UPCStore] Returning " + std::to_string(DlcStrings.size()) + " items");
    return true;
}

} // namespace Uues::EmuUPC