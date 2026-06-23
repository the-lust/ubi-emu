#include "DbDataSecureDlcHandler.hpp"
#include "../Core/Log/Logger.hpp"
#include <algorithm>

namespace Uues::EmuDbData {
using namespace Uues::Core;

DbDataSecureDlcHandler& DbDataSecureDlcHandler::GetInstance() {
    static DbDataSecureDlcHandler Instance;
    return Instance;
}

DbDataSecureDlcHandler::DbDataSecureDlcHandler() {
    Log::Logger::GetInstance().Debug("[DbDataSecureDlc] Handler created");
}

Common::ByteArray DbDataSecureDlcHandler::HandleRequest(const Common::ByteArray& Request) {
    if (Request.empty()) {
        Log::Logger::GetInstance().Warning("[DbDataSecureDlc] Empty request, returning empty response");
        return {};
    }

    Log::Logger::GetInstance().Debug("[DbDataSecureDlc] Handling request (" +
        std::to_string(Request.size()) + " bytes)");

    // in a real implementation we'd parse the protobuf request here
    // for now just build whatever we have cached
    auto OwnedToken = mBuilder.BuildSignedOwnershipList();
    return OwnedToken;
}

Common::ByteArray DbDataSecureDlcHandler::BuildResponse(const Common::StringList& Dlcs) {
    if (Dlcs.empty()) {
        Log::Logger::GetInstance().Warning("[DbDataSecureDlc] Building response with empty DLC list");
    }
    for (auto& Dlc : Dlcs) mBuilder.AddDlc(Dlc);
    auto Result = mBuilder.BuildSignedOwnershipList();
    Log::Logger::GetInstance().Info("[DbDataSecureDlc] Built response for " +
        std::to_string(Dlcs.size()) + " DLCs (" +
        std::to_string(Result.size()) + " bytes)");
    return Result;
}

void DbDataSecureDlcHandler::SetBaseAppId(const Common::String& AppId) {
    if (AppId.empty()) {
        Log::Logger::GetInstance().Warning("[DbDataSecureDlc] SetBaseAppId with empty AppId");
        return;
    }
    mBuilder.SetBaseAppId(AppId);
}

void DbDataSecureDlcHandler::SetUserId(const Common::String& UserId) {
    if (UserId.empty()) {
        Log::Logger::GetInstance().Warning("[DbDataSecureDlc] SetUserId with empty UserId");
        return;
    }
    mBuilder.SetUserId(UserId);
}

} // namespace Uues::EmuDbData
