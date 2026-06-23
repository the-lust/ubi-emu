#include "../Core/Log/Logger.hpp"
#include "../Core/Common/Types.hpp"
#include "../Core/Ini/IniParser.hpp"
#include <cstdio>
#include <cassert>
#include <cstring>

static int sPassed = 0;
static int sFailed = 0;

#define TEST(name) do { printf("  TEST: %-30s ", name);
#define PASS() do { printf("PASSED\n"); sPassed++; } while(0)
#define FAIL(msg) do { printf("FAILED: %s\n", msg); sFailed++; } while(0)
#define END_TEST() } while(0)

void TestLogger() {
    auto& Logger = Uues::Core::Log::Logger::GetInstance();
    Logger.Info("Test info message");
    Logger.Warning("Test warning message");
    Logger.Error("Test error message");
    PASS();
    END_TEST();
}

void TestTypes() {
    Uues::Core::Common::String S = "hello";
    if (S.size() == 5) PASS(); else FAIL("string size");
    END_TEST();

    Uues::Core::Common::StringList List = {"a", "b", "c"};
    if (List.size() == 3) PASS(); else FAIL("list size");
    END_TEST();
}

void TestIni() {
    Uues::Core::Ini::IniParser P;
    if (!P.LoadFromString("[test]\nkey=val\n")) { FAIL("parse"); return; }
    if (P.GetValue("test", "key") == "val") PASS(); else FAIL("value");
    END_TEST();
}

void TestMath() {
    // small sanity
    int X = 2 + 2;
    if (X == 4) PASS(); else FAIL("2+2 != 4");
    END_TEST();
}

int main() {
    printf("CoreTests\n");
    printf("=========\n");
    TestLogger();
    TestTypes();
    TestIni();
    TestMath();
    printf("Results: %d passed, %d failed\n", sPassed, sFailed);
    return sFailed > 0 ? 1 : 0;
}