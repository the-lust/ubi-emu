# R2 emulator — evolved from R1, more API surface
# TODO: split this into separate modules if it gets bigger

set(R2_SOURCES
    R2Loader.cpp
    R2Exports.cpp
    R2InitHandler.cpp
    R2ConfigReader.cpp
    R2StateManager.cpp
    R2UserHandler.cpp
    R2AchievementHandler.cpp
    R2DlcHandler.cpp
    R2SaveHandler.cpp
    R2OverlayHandler.cpp
    R2PartyHandler.cpp
    R2StatsHandler.cpp
    R2StoreHandler.cpp
)

set(R2_HEADERS
    R2Loader.hpp
    R2Exports.hpp
    R2InitHandler.hpp
    R2ConfigReader.hpp
    R2StateManager.hpp
    R2UserHandler.hpp
    R2AchievementHandler.hpp
    R2DlcHandler.hpp
    R2SaveHandler.hpp
    R2OverlayHandler.hpp
    R2PartyHandler.hpp
    R2StatsHandler.hpp
    R2StoreHandler.hpp
)

add_library(EmuR2 SHARED ${R2_SOURCES} ${R2_HEADERS})
target_link_libraries(EmuR2 PRIVATE LibUbi)
target_include_directories(EmuR2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    set_target_properties(EmuR2 PROPERTIES
        SUFFIX ".dll"
        PREFIX ""
        OUTPUT_NAME "uplay_r2_loader"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin/R2"
    )
endif()
