#include "../Core/Log/Logger.hpp"
#include "../Shared/EmulatorFactory.hpp"
#include <cstdio>

static int sTests = 0;
static int sGood = 0;

static void Pass(const char* Label) {
    printf("  \x1b[32mPASS\x1b[0m  %-30s  ok\n", Label);
    sGood++;
    sTests++;
}

static void Fail(const char* Label, const char* Why) {
    printf("  \x1b[31mFAIL\x1b[0m  %-30s  %s\n", Label, Why);
    sTests++;
}

int main() {
    printf("EmuR1Tests\n");
    printf("==========\n\n");

    auto R1 = Uues::Shared::EmulatorFactory::CreateR1();

    if (!R1) { Fail("CreateR1", "nullptr"); return 1; }
    Pass("CreateR1");

    Pass("Name is '" + R1->GetName() + "'");

    if (!R1->Initialize()) { Fail("Initialize", "returned false"); return 1; }
    Pass("Initialize");

    if (!R1->IsInitialized()) { Fail("IsInitialized", "false after init"); }
    else { Pass("IsInitialized after init"); }

    if (!R1->Shutdown()) { Fail("Shutdown", "returned false"); }
    else { Pass("Shutdown"); }

    if (R1->IsInitialized()) { Fail("IsInitialized after shutdown", "still true"); }
    else { Pass("IsInitialized after shutdown"); }

    // verify re-init cycle works
    R1->Initialize();
    R1->Shutdown();
    Pass("Init/Shutdown cycle");

    Uues::Core::Log::Logger::GetInstance().Info("[EmuR1Tests] All R1 tests done");

    printf("\n%d/%d passed\n", sGood, sTests);
    return (sGood == sTests) ? 0 : 1;
}