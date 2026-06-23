#include "../Core/Log/Logger.hpp"
#include "../Shared/EmulatorFactory.hpp"
#include <cstdio>
#include <string>
#include <cassert>

static int sOk = 0;
static int sBad = 0;

#define INTEG_TEST(name, expr) do { \
    printf("  [INTEG] %-30s ", name); \
    if (expr) { printf("OK\n"); sOk++; } \
    else { printf("FAIL\n"); sBad++; } \
} while(0)

int main() {
    printf("IntegrationTests\n");
    printf("================\n");

    // --- Emulator creation ---
    auto R1    = Uues::Shared::EmulatorFactory::CreateR1();
    auto R2    = Uues::Shared::EmulatorFactory::CreateR2();
    auto UPC   = Uues::Shared::EmulatorFactory::CreateUPC();
    auto Orbit = Uues::Shared::EmulatorFactory::CreateOrbit();

    INTEG_TEST("CreateR1",       R1.get() != nullptr);
    INTEG_TEST("CreateR2",       R2.get() != nullptr);
    INTEG_TEST("CreateUPC",      UPC.get() != nullptr);
    INTEG_TEST("CreateOrbit",    Orbit.get() != nullptr);

    // --- EmulatorInterface conformance ---
    INTEG_TEST("R1 has name",    R1  && !R1->GetName().empty());
    INTEG_TEST("R2 has name",    R2  && !R2->GetName().empty());
    INTEG_TEST("UPC has name",   UPC && !UPC->GetName().empty());
    INTEG_TEST("Orbit has name", Orbit && !Orbit->GetName().empty());

    INTEG_TEST("R1 has version",    R1  && !R1->GetVersion().empty());
    INTEG_TEST("Orbit has version", Orbit && !Orbit->GetVersion().empty());

    // --- Init lifecycle ---
    if (Orbit) {
        INTEG_TEST("Orbit init",      Orbit->Initialize());
        INTEG_TEST("Orbit is init'd", Orbit->IsInitialized());
        INTEG_TEST("Orbit shutdown",  Orbit->Shutdown());
        INTEG_TEST("Orbit not init'd", !Orbit->IsInitialized());
    }

    // --- Factory registry ---
    auto Custom = Uues::Shared::EmulatorFactory::CreateEmulator("nonexistent");
    INTEG_TEST("Unknown type fails", Custom.get() == nullptr);

    printf("----------------\n");
    printf("Results: %d passed, %d failed\n", sOk, sBad);
    return (sBad > 0) ? 1 : 0;
}