# Orbit emulator — older ubisoft DRM, smaller API surface
# FIXME: there's a delay in OrbitUserHandler that needs investigation

set(ORBIT_SOURCES
    OrbitLoader.cpp
    OrbitExports.cpp
    OrbitInitHandler.cpp
    OrbitConfigReader.cpp
    OrbitStateManager.cpp
    OrbitUserHandler.cpp
    OrbitDlcHandler.cpp
    OrbitSaveHandler.cpp
    OrbitNetworkHandler.cpp
)

set(ORBIT_HEADERS
    OrbitLoader.hpp
    OrbitExports.hpp
    OrbitInitHandler.hpp
    OrbitConfigReader.hpp
    OrbitStateManager.hpp
    OrbitUserHandler.hpp
    OrbitDlcHandler.hpp
    OrbitSaveHandler.hpp
    OrbitNetworkHandler.hpp
)

add_library(EmuOrbit SHARED ${ORBIT_SOURCES} ${ORBIT_HEADERS})
target_link_libraries(EmuOrbit PRIVATE LibUbi)
target_include_directories(EmuOrbit PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    set_target_properties(EmuOrbit PROPERTIES
        SUFFIX ".dll"
        PREFIX ""
        OUTPUT_NAME "ubiorbitapi_r2_loader"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin/Orbit"
    )
endif()
