# Shared DLL infrastructure
# this is the bootstrap that gets loaded by the game

set(SHARED_SOURCES
    DllMain.cpp
    DllEntryPoint.cpp
    EmulatorBase.cpp
    EmulatorFactory.cpp
    EmulatorInterface.cpp
)

set(SHARED_HEADERS
    DllMain.hpp
    DllEntryPoint.hpp
    EmulatorBase.hpp
    EmulatorFactory.hpp
    EmulatorInterface.hpp
)

add_library(EmuShared SHARED ${SHARED_SOURCES} ${SHARED_HEADERS})
target_link_libraries(EmuShared PRIVATE LibUbi)

# include current dir for header inter-dependencies
target_include_directories(EmuShared PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
