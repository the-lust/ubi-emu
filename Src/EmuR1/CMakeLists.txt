# R1 emulator — the original, kinda messy but it works
# added handlers as we discovered more uplay_r1 endpoints
set(R1_SOURCES
    R1Loader.cpp
    R1ConfigReader.cpp
    R1StateManager.cpp
    R1Exports.cpp
    R1InitHandler.cpp
    R1UserHandler.cpp
    R1SaveHandler.cpp
    R1AchievementHandler.cpp
    R1DlcHandler.cpp
    R1OverlayHandler.cpp
    R1PartyHandler.cpp
    R1AvatarHandler.cpp
    R1FriendHandler.cpp
    R1RichPresenceHandler.cpp
)

set(R1_HEADERS
    R1Loader.hpp
    R1ConfigReader.hpp
    R1StateManager.hpp
    R1Exports.hpp
    R1InitHandler.hpp
    R1UserHandler.hpp
    R1SaveHandler.hpp
    R1AchievementHandler.hpp
    R1DlcHandler.hpp
    R1OverlayHandler.hpp
    R1PartyHandler.hpp
    R1AvatarHandler.hpp
    R1FriendHandler.hpp
    R1RichPresenceHandler.hpp
)

add_library(EmuR1 SHARED ${R1_SOURCES} ${R1_HEADERS})
target_link_libraries(EmuR1 PRIVATE LibUbi)

# need source dir because headers reference each other internally
target_include_directories(EmuR1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    set_target_properties(EmuR1 PROPERTIES
        SUFFIX ".dll"
        PREFIX ""
        OUTPUT_NAME "uplay_r1_loader"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin/R1"
    )
endif()
