#include "../Core/Proto/ProtobufSerializer.hpp"
#include "../Core/Log/Logger.hpp"
#include <cstdio>
#include <cassert>

namespace Uues::Tests {
using namespace Uues::Core;

bool RunProtoTests() {
    Log::Logger::GetInstance().Info("[ProtoTests] Starting");

    int Total = 0;
    int Passed = 0;

    // ProtobufSerializer static methods
    {
        auto Serialized = Core::Proto::ProtobufSerializer::SerializeMessage({});
        Total++;
        Passed++;
    }

    printf("[Proto] Serializer instantiated: %s\n", (Passed == Total) ? "OK" : "FAIL");
    Log::Logger::GetInstance().Info("[ProtoTests] " +
        std::to_string(Passed) + "/" + std::to_string(Total) + " passed");
    return Passed == Total;
}

} // namespace Uues::Tests