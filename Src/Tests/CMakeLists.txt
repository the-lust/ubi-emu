if(BUILD_TESTS)
    enable_testing()

    add_executable(CoreTests
        TestIniParser.cpp
        TestConfig.cpp
        TestCrypto.cpp
        TestThreading.cpp
        TestMemory.cpp
        TestNet.cpp
        TestProto.cpp
        TestStorage.cpp
        TestLogger.cpp
        CoreTests.cpp
    )
    target_link_libraries(CoreTests PRIVATE LibUbi)
    target_include_directories(CoreTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME CoreTests COMMAND CoreTests)

    add_executable(EmuR1Tests
        EmuR1Tests.cpp
    )
    target_link_libraries(EmuR1Tests PRIVATE EmuR1 LibUbi)
    target_include_directories(EmuR1Tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME EmuR1Tests COMMAND EmuR1Tests)

    add_executable(EmuR2Tests
        EmuR2Tests.cpp
    )
    target_link_libraries(EmuR2Tests PRIVATE EmuR2 LibUbi)
    target_include_directories(EmuR2Tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME EmuR2Tests COMMAND EmuR2Tests)

    add_executable(EmuUPCTests
        EmuUPCTests.cpp
    )
    target_link_libraries(EmuUPCTests PRIVATE EmuUPC LibUbi)
    target_include_directories(EmuUPCTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME EmuUPCTests COMMAND EmuUPCTests)

    add_executable(EmuOrbitTests
        EmuOrbitTests.cpp
    )
    target_link_libraries(EmuOrbitTests PRIVATE EmuOrbit LibUbi)
    target_include_directories(EmuOrbitTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME EmuOrbitTests COMMAND EmuOrbitTests)

    add_executable(EmuDbDataTests
        EmuDbDataTests.cpp
    )
    target_link_libraries(EmuDbDataTests PRIVATE EmuDbData LibUbi)
    target_include_directories(EmuDbDataTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME EmuDbDataTests COMMAND EmuDbDataTests)

    add_executable(IntegrationTests
        IntegrationTests.cpp
    )
    target_link_libraries(IntegrationTests PRIVATE EmuR1 EmuR2 EmuUPC EmuOrbit EmuDbData LibUbi)
    target_include_directories(IntegrationTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME IntegrationTests COMMAND IntegrationTests)
endif()
