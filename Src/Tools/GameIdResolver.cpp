#include "GameIdResolver.hpp"
#include "../Core/Log/Logger.hpp"
#include <unordered_map>

namespace Uues::Tools {
using namespace Uues::Core;

// hardcoded known mappings until we ship the real database
const static std::unordered_map<int, Common::String> sKnownIds = {
    { 13504, "Far Cry 3" },
    { 13506, "Far Cry 3 - Blood Dragon" },
    { 22000, "Far Cry 4" },
    { 18000, "Assassin's Creed IV" },
    { 33230, "Assassin's Creed Unity" },
    { 35900, "Far Cry Primal" },
    { 17930, "Watch Dogs" },
    { 27330, "Rainbow Six Siege" },
};

int GameIdResolver::ResolveAppId(const Common::String& GameName) {
    Log::Logger::GetInstance().Info("[GameIdResolver] Resolving AppId for '" + GameName + "'");

    if (GameName.empty()) {
        Log::Logger::GetInstance().Warning("[GameIdResolver] Empty game name");
        return 0;
    }

    for (auto& [Id, Name] : sKnownIds) {
        if (Name == GameName) return Id;
    }

    Log::Logger::GetInstance().Warning("[GameIdResolver] Unknown game '" + GameName + "', returning 0");
    return 0;
}

Common::String GameIdResolver::ResolveGameName(int AppId) {
    Log::Logger::GetInstance().Info("[GameIdResolver] Resolving game name for AppId " + std::to_string(AppId));

    if (AppId <= 0) {
        return "Unknown";
    }

    auto It = sKnownIds.find(AppId);
    if (It != sKnownIds.end()) return It->second;

    Log::Logger::GetInstance().Warning("[GameIdResolver] Unknown AppId " + std::to_string(AppId));
    return "Unknown";
}

} // namespace Uues::Tools
