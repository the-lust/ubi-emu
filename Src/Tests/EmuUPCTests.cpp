#include "../Shared/EmulatorFactory.hpp"
#include <cstdio>
#include <string>

static int sTestNo = 0;
static int sPass = 0;
static int sFail = 0;

#define OK(desc) do { printf("  ok %d: %s\n", ++sTestNo, desc); sPass++; } while(0)
#define NOTOK(desc) do { printf("  FAIL %d: %s\n", ++sTestNo, desc); sFail++; } while(0)
#define CHECK(cond, desc) do { if (cond) OK(desc); else NOTOK(desc); } while(0)

int main() {
    printf("EmuUPCTests\n");
    printf("===========\n\n");

    printf("--- Factory ---\n");
    auto Emu = Uues::Shared::EmulatorFactory::CreateUPC();
    CHECK(Emu != nullptr, "UPC emulator created");

    printf("\n--- Identity ---\n");
    CHECK(Emu->GetName().find("UPC") != std::string::npos ||
          Emu->GetName().find("Upc") != std::string::npos,
          "Name contains 'UPC'");
    CHECK(Emu->GetVersion().size() > 0, "Version string non-empty");

    printf("\n--- Lifecycle ---\n");
    CHECK(Emu->Initialize(), "Initialize succeeds");
    CHECK(Emu->IsInitialized(), "IsInitialized after init");
    Emu->Shutdown();
    CHECK(!Emu->IsInitialized(), "Not initialized after shutdown");

    printf("\n--- Config ---\n");
    CHECK(Emu->LoadConfig("test.ini"), "LoadConfig returns true");
    CHECK(Emu->GetVersion() >= "1.0.0.0", "Version >= 1.0.0.0");

    printf("\n= %d passed, %d failed =\n", sPass, sFail);
    return sFail > 0 ? 1 : 0;
}