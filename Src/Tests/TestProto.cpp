#include "../Core/Proto/ProtobufSerializer.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstdio>
#include <cassert>

namespace Uues::Tests {

bool RunProtoTests() {
    Log::Logger::GetInstance().Info("[ProtoTests] Starting");

    int Total = 0;
    int Passed = 0;

    // ProtobufSerializer create/destroy
    {
        auto& S = Core::Proto::ProtobufSerializer::GetInstance();
        Total++;
        // just verify it doesn't crash
        Passed++;
    }

    printf("[Proto] Serializer instantiated: %s\n", (Passed == Total) ? "OK" : "FAIL");
    Log::Logger::GetInstance().Info("[ProtoTests] " +
        std::to_string(Passed) + "/" + std::to_string(Total) + " passed");
    return Passed == Total;
}

} // namespace Uues::Tests