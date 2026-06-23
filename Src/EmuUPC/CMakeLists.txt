# UPC (uPlay PC) emulator — has its own weird protocol
# DemuxHandler was a pain to reverse engineer

set(UPC_SOURCES
    UpcLoader.cpp
    UpcExports.cpp
    UpcConfigReader.cpp
    UpcInitHandler.cpp
    UpcAuthHandler.cpp
    UpcDemuxHandler.cpp
    UpcProductHandler.cpp
    UpcAchievementHandler.cpp
    UpcDlcHandler.cpp
    UpcSaveHandler.cpp
    UpcOverlayHandler.cpp
    UpcPartyHandler.cpp
    UpcStoreHandler.cpp
    UpcStateManager.cpp
)

set(UPC_HEADERS
    UpcLoader.hpp
    UpcExports.hpp
    UpcConfigReader.hpp
    UpcInitHandler.hpp
    UpcAuthHandler.hpp
    UpcDemuxHandler.hpp
    UpcProductHandler.hpp
    UpcAchievementHandler.hpp
    UpcDlcHandler.hpp
    UpcSaveHandler.hpp
    UpcOverlayHandler.hpp
    UpcPartyHandler.hpp
    UpcStoreHandler.hpp
    UpcStateManager.hpp
)

add_library(EmuUPC SHARED ${UPC_SOURCES} ${UPC_HEADERS})
target_link_libraries(EmuUPC PRIVATE LibUbi)
target_include_directories(EmuUPC PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    set_target_properties(EmuUPC PROPERTIES
        SUFFIX ".dll"
        PREFIX ""
        OUTPUT_NAME "upc_r1_loader"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin/UPC"
    )
endif()
