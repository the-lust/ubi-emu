#include "../Core/Log/Logger.hpp"
#include "../EmuDbData/DbDataStateManager.hpp"
#include "../EmuDbData/DbDataOwnershipHandler.hpp"
#include <cstdio>
#include <cassert>

static int gFailures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        printf("  FAIL: %s (line %d)\n", msg, __LINE__); \
        gFailures++; \
    } else { \
        printf("  PASS: %s\n", msg); \
    } \
} while(0)

int main() {
    printf("EmuDbDataTests\n");
    printf("==============\n\n");

    using namespace Uues::EmuDbData;

    // --- StateManager ---
    auto& SM = DbDataStateManager::GetInstance();
    CHECK(!SM.IsInitialized(), "StateManager starts uninitialized");

    Uues::Core::Config::EmulatorConfig Cfg;
    Cfg.UserName = "TestUser";
    SM.SetConfig(Cfg);
    CHECK(SM.IsInitialized(), "StateManager initialized after SetConfig");
    CHECK(SM.GetConfig().UserName == "TestUser", "UserName persisted");

    SM.Reset();
    CHECK(!SM.IsInitialized(), "StateManager reset clears init flag");

    // --- OwnershipHandler singleton ---
    auto& OH = DbDataOwnershipHandler::GetInstance();
    auto& OH2 = DbDataOwnershipHandler::GetInstance();
    CHECK(&OH == &OH2, "OwnershipHandler is singleton");

    CHECK(OH.CheckOwnership(42), "OwnAll is true by default, so 42 is owned");

    OH.SetOwnAll(false);
    CHECK(!OH.CheckOwnership(42), "After OwnAll=false, 42 is NOT owned");

    OH.AddOwnedDlc(42);
    CHECK(OH.CheckOwnership(42), "After AddOwnedDlc(42), it is owned");
    CHECK(!OH.CheckOwnership(99), "DLC 99 still not owned");

    // --- Ownership list ---
    OH.SetOwnAll(false);
    OH.AddOwnedDlc(100);
    OH.AddOwnedDlc(200);
    auto List = OH.GetOwnershipList();
    std::string ListStr(List.begin(), List.end());
    CHECK(ListStr.find("100") != std::string::npos, "List contains 100");
    CHECK(ListStr.find("200") != std::string::npos, "List contains 200");

    printf("\nResult: %d failure(s)\n", gFailures);
    return gFailures > 0 ? 1 : 0;
}