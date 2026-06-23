#include "../EmuOrbit/OrbitInitHandler.hpp"
#include "../EmuOrbit/OrbitStateManager.hpp"
#include "../EmuOrbit/OrbitNetworkHandler.hpp"
#include <cstdio>

static int sPassed = 0;
static int sFailed = 0;

#define T(name, expr) do { \
    printf("  %-40s ", name); \
    if (expr) { printf("PASS\n"); sPassed++; } \
    else { printf("FAIL\n"); sFailed++; } \
} while(0)

int main() {
    printf("EmuOrbitTests\n");
    printf("=============\n\n");

    using namespace Uues::EmuOrbit;

    printf("--- InitHandler ---\n");
    T("init with valid AppId",   OrbitInitHandler::HandleInit(100, 12345));
    T("is initialized",          OrbitInitHandler::IsInitialized());
    T("re-init same is OK",      OrbitInitHandler::HandleInit(100, 12345));
    T("StateManager holds AppId", OrbitStateManager::GetInstance().GetAppId() == 12345);
    T("shutdown",                OrbitInitHandler::HandleShutdown());
    T("not initialized after",   !OrbitInitHandler::IsInitialized());

    printf("\n--- NetworkHandler ---\n");
    T("connect to localhost",    OrbitNetworkHandler::Connect("127.0.0.1", 80));
    T("is connected",            OrbitNetworkHandler::IsConnected());
    T("disconnect",              OrbitNetworkHandler::Disconnect());
    T("not connected",           !OrbitNetworkHandler::IsConnected());
    T("connect rejected empty",  !OrbitNetworkHandler::Connect("", 80));

    printf("\n--- StateManager ---\n");
    OrbitStateManager::GetInstance().Reset();
    T("AppId default 0",        OrbitStateManager::GetInstance().GetAppId() == 0);
    OrbitStateManager::GetInstance().SetAppId(99);
    T("AppId set to 99",        OrbitStateManager::GetInstance().GetAppId() == 99);

    printf("\n=== %d passed, %d failed ===\n", sPassed, sFailed);
    return sFailed > 0 ? 1 : 0;
}