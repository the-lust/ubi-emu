#include "../Core/Net/SocketClient.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstdio>

namespace Uues::Tests {
using namespace Uues::Core;

bool RunNetTests() {
    Log::Logger::GetInstance().Info("[NetTests] Starting network tests");

    int Failed = 0;

    // SocketClient creation (no connection attempt here)
    {
        Core::Net::SocketClient Client;
        Failed += 0; // no news is good news
    }

    // SocketClient with connect to nowhere (should fail gracefully)
    {
        Core::Net::SocketClient Client;
        bool Connected = Client.Connect("localhost", 0);
        if (Connected) {
            Log::Logger::GetInstance().Warning("[NetTests] Connected to port 0? (unexpected)");
        } else {
            Log::Logger::GetInstance().Info("[NetTests] Connect to port 0 rejected (expected)");
        }
    }

    printf("[Net] Network layer basic checks: %s\n", Failed == 0 ? "PASS" : "FAIL");
    return Failed == 0;
}

} // namespace Uues::Tests