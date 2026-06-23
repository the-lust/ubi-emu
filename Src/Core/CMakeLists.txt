# Core library — this kinda grew organically as we added features
# started as just ini parsing, now its a whole framework

set(LIBUBI_SOURCES
    # Common utilities — foundational stuff everything uses
    Common/BufferUtils.cpp
    Common/StringUtils.cpp
    Common/FileUtils.cpp
    Common/TimeUtils.cpp
    Common/Errors.cpp
    Common/GuidGenerator.cpp

    # Platform layer — needs to be early for arch detection
    Platform/ModuleLoader.cpp
    Platform/WindowsPlatform.cpp
    Platform/LinuxPlatform.cpp
    Platform/ArchitectureDetector.cpp
    Platform/ExportTable.cpp
    Platform/ImportTable.cpp

    # Memory tools — added when we needed to scan game memory
    Memory/MemoryAllocator.cpp
    Memory/MemoryScanner.cpp
    Memory/MemoryPatcher.cpp
    Memory/PointerGuard.cpp

    # Ini parser — grew way more complex than expected
    Ini/IniParser.cpp
    Ini/IniSection.cpp
    Ini/IniKey.cpp
    Ini/IniComment.cpp
    Ini/IniType.cpp
    Ini/IniValue.cpp

    # Crypto — ticket generation and signature verification
    Crypto/AesEncryptor.cpp
    Crypto/RsaSigner.cpp
    Crypto/ShaHasher.cpp
    Crypto/HmacHasher.cpp
    Crypto/TicketGenerator.cpp
    Crypto/TokenParser.cpp
    Crypto/OwnershipListBuilder.cpp

    # Networking — sockets and named pipes for IPC
    Net/SocketClient.cpp
    Net/SocketServer.cpp
    Net/HttpRequest.cpp
    Net/HttpResponse.cpp
    Net/NamedPipeClient.cpp
    Net/NamedPipeServer.cpp
    Net/PacketBuilder.cpp
    Net/PacketParser.cpp
    Net/AddressResolver.cpp
    Net/DnsCache.cpp

    # Protocol buffers — serialization layer
    Proto/ProtobufSerializer.cpp
    Proto/ProtobufDeserializer.cpp
    Proto/DemuxMessage.cpp
    Proto/DemuxRouter.cpp
    Proto/ProtoField.cpp
    Proto/ProtoSchema.cpp

    # Logging — added after we got tired of printf debugging
    Log/Logger.cpp
    Log/LogLevel.cpp
    Log/LogTarget.cpp
    Log/ConsoleTarget.cpp
    Log/FileTarget.cpp
    Log/DebugOutputTarget.cpp

    # Hooking — the fun stuff, API interception
    Hook/MinHookManager.cpp
    Hook/DetourBuilder.cpp
    Hook/TrampolineAllocator.cpp
    Hook/HookContext.cpp

    # Config management — uses Ini parser internally
    Config/EmulatorConfig.cpp
    Config/ConfigDefaults.cpp
    Config/ConfigValidator.cpp

    # Storage — save data, achievements, dlc
    Storage/SaveManager.cpp
    Storage/SavePathResolver.cpp
    Storage/DlcManager.cpp
    Storage/AchievementManager.cpp
    Storage/UserProfile.cpp
    Storage/ProfileSerializer.cpp

    # Threading — thread pool and sync primitives
    Threading/ThreadPool.cpp
    Threading/TaskQueue.cpp
    Threading/CriticalSection.cpp
    Threading/EventSignal.cpp
)

set(LIBUBI_HEADERS
    # Common headers — note: Macros.hpp must be included first everywhere
    Common/Macros.hpp
    Common/Types.hpp
    Common/Constants.hpp
    Common/Errors.hpp
    Common/Version.hpp
    Common/BufferUtils.hpp
    Common/StringUtils.hpp
    Common/FileUtils.hpp
    Common/TimeUtils.hpp
    Common/GuidGenerator.hpp

    Platform/ModuleLoader.hpp
    Platform/WindowsPlatform.hpp
    Platform/LinuxPlatform.hpp
    Platform/ArchitectureDetector.hpp
    Platform/ExportTable.hpp
    Platform/ImportTable.hpp

    Memory/MemoryAllocator.hpp
    Memory/MemoryScanner.hpp
    Memory/MemoryPatcher.hpp
    Memory/PointerGuard.hpp

    Ini/IniParser.hpp
    Ini/IniSection.hpp
    Ini/IniKey.hpp
    Ini/IniComment.hpp
    Ini/IniType.hpp
    Ini/IniValue.hpp

    Crypto/AesEncryptor.hpp
    Crypto/RsaSigner.hpp
    Crypto/ShaHasher.hpp
    Crypto/HmacHasher.hpp
    Crypto/TicketGenerator.hpp
    Crypto/TokenParser.hpp
    Crypto/OwnershipListBuilder.hpp

    Net/SocketClient.hpp
    Net/SocketServer.hpp
    Net/HttpRequest.hpp
    Net/HttpResponse.hpp
    Net/NamedPipeClient.hpp
    Net/NamedPipeServer.hpp
    Net/PacketBuilder.hpp
    Net/PacketParser.hpp
    Net/AddressResolver.hpp
    Net/DnsCache.hpp

    Proto/ProtobufSerializer.hpp
    Proto/ProtobufDeserializer.hpp
    Proto/DemuxMessage.hpp
    Proto/DemuxRouter.hpp
    Proto/ProtoField.hpp
    Proto/ProtoSchema.hpp

    Log/Logger.hpp
    Log/LogLevel.hpp
    Log/LogTarget.hpp
    Log/ConsoleTarget.hpp
    Log/FileTarget.hpp
    Log/DebugOutputTarget.hpp

    Hook/MinHookManager.hpp
    Hook/DetourBuilder.hpp
    Hook/TrampolineAllocator.hpp
    Hook/HookContext.hpp

    Config/EmulatorConfig.hpp
    Config/ConfigDefaults.hpp
    Config/ConfigValidator.hpp

    Storage/SaveManager.hpp
    Storage/SavePathResolver.hpp
    Storage/DlcManager.hpp
    Storage/AchievementManager.hpp
    Storage/UserProfile.hpp
    Storage/ProfileSerializer.hpp

    Threading/ThreadPool.hpp
    Threading/TaskQueue.hpp
    Threading/CriticalSection.hpp
    Threading/EventSignal.hpp
)

add_library(LibUbi STATIC ${LIBUBI_SOURCES} ${LIBUBI_HEADERS})

# Expose current dir so subprojects can include our public headers
target_include_directories(LibUbi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(ENABLE_LOGGING)
    target_compile_definitions(LibUbi PUBLIC UUES_ENABLE_LOGGING=1)
endif()

if(ENABLE_PROTOBUF)
    target_compile_definitions(LibUbi PUBLIC UUES_ENABLE_PROTOBUF=1)
endif()

if(WIN32)
    # ws2_32 for winsock, crypt32 for certificate stuff
    target_link_libraries(LibUbi PUBLIC ws2_32 crypt32)
endif()
