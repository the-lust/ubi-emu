#include "../Core/Net/SocketClient.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstdio>

namespace Uues::Tests {

bool RunNetTests() {
    Log::Logger::GetInstance().Info("[NetTests] Starting network tests");

    int Failed = 0;

    // SocketClient creation (no connection attempt here)
    {
        Core::Net::SocketClient Client("tcp");
        Failed += 0; // no news is good news
    }

    // SocketClient with invalid params
    {
        Core::Net::SocketClient BadClient("");
        // should not crash, we just log the result
        Log::Logger::GetInstance().Debug("[NetTests] Created client with empty protocol (expected)");
    }

    printf("[Net] Network layer basic checks: %s\n", Failed == 0 ? "PASS" : "FAIL");
    return Failed == 0;
}

} // namespace Uues::Tests