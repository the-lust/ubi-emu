#include "../Shared/EmulatorFactory.hpp"
#include <cstdio>
#include <cassert>

enum Result { R_PASS, R_FAIL };
static int sTotal = 0;
static int sGood = 0;

static void Test(const char* Name, Result R) {
    sTotal++;
    if (R == R_PASS) { sGood++; printf("  [OK]  %s\n", Name); }
    else { printf("  [!!]  %s\n", Name); }
}

int main() {
    printf("EmuR2Tests\n");
    printf("==========\n\n");

    auto R2 = Uues::Shared::EmulatorFactory::CreateR2();
    Test("R2 instance created", R2 ? R_PASS : R_FAIL);
    if (!R2) {
        Test("all remaining skipped", R_FAIL);
        printf("\n%d / %d passed\n", sGood, sTotal);
        return 1;
    }

    Test("GetName non-empty", !R2->GetName().empty() ? R_PASS : R_FAIL);
    Test("GetVersion non-empty", !R2->GetVersion().empty() ? R_PASS : R_FAIL);

    // double-init should be safe
    Test("first init",  R2->Initialize() ? R_PASS : R_FAIL);
    Test("second init (idempotent)", R2->Initialize() ? R_PASS : R_FAIL);
    Test("is initialized after init", R2->IsInitialized() ? R_PASS : R_FAIL);

    // shutdown
    Test("shutdown", R2->Shutdown() ? R_PASS : R_FAIL);
    Test("not init'd after shutdown", !R2->IsInitialized() ? R_PASS : R_FAIL);

    // shutdown when already down is handled gracefully
    bool ShutdownAgain = R2->Shutdown();
    Test("shutdown twice graceful", !ShutdownAgain ? R_PASS : R_FAIL);

    printf("\n%d / %d tests passed\n", sGood, sTotal);
    return (sGood == sTotal) ? 0 : 1;
}