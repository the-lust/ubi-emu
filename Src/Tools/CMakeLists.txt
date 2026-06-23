# Utility tools — converters and validators for config files
# Most of these were written ad-hoc for specific conversion needs

set(TOOLS_SOURCES
    GoldbergImporter.cpp
    GoldbergImporter.hpp
    ColdApiImporter.cpp
    ColdApiImporter.hpp
    LumaPlayImporter.cpp
    LumaPlayImporter.hpp
    UnlockerJsonImporter.cpp
    UnlockerJsonImporter.hpp
    IniToUbiIniConverter.cpp
    IniToUbiIniConverter.hpp
    ExportValidator.cpp
    ExportValidator.hpp
    GameIdResolver.cpp
    GameIdResolver.hpp
)

add_library(UuesTools ${TOOLS_SOURCES})
target_link_libraries(UuesTools PRIVATE LibUbi)
target_include_directories(UuesTools PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
