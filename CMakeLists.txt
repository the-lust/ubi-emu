cmake_minimum_required(VERSION 3.20)
project(UUES VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# --- Build options ---
# Tests and tools default to ON so CI catches regressions early
option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_TOOLS "Build utility tools" ON)
option(BUILD_EXAMPLES "Build example configurations" OFF)
option(ENABLE_LOGGING "Enable logging subsystem" ON)
option(ENABLE_PROTOBUF "Enable protobuf support" ON)

# --- Platform-specific compile flags ---
if(MSVC)
    # /MP for parallel builds, /utf-8 because some game configs have weird chars
    add_compile_options(/W4 /utf-8 /MP)
else()
    # We use -Werror in CI but not here - third party headers are unpredictable
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- Subdirectories ---
# Src must be first, tools and tests depend on it
add_subdirectory(Src)



# TODO: add install() rules once we settle on a directory layout
# also should probably handle CPack for releases
