#include "UpcProductHandler.hpp"
#include "../Core/Log/Logger.hpp"

namespace Uues::EmuUPC {
using namespace Uues::Core;

static int sProductId = 0;
// FIXME: some games pass product IDs that look wrong
// need to verify against known product list

int UpcProductHandler::GetProductId() {
    Log::Logger::GetInstance().Debug("[UPCProduct] GetProductId = " + std::to_string(sProductId));
    return sProductId;
}

bool UpcProductHandler::SetProductId(int id) {
    if (id < 0) {
        Log::Logger::GetInstance().Warning("[UPCProduct] Negative product ID: " + std::to_string(id));
        return false;
    }
    sProductId = id;
    Log::Logger::GetInstance().Info("[UPCProduct] SetProductId = " + std::to_string(id));
    return true;
}

} // namespace Uues::EmuUPC
