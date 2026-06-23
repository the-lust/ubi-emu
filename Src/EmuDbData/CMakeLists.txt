# DbData — handles secure storage, tickets, and licensing
# This one interfaces directly with the dbdata service

set(DBDATA_SOURCES
    DbDataLoader.cpp
    DbDataExports.cpp
    DbDataInitHandler.cpp
    DbDataConfigReader.cpp
    DbDataStateManager.cpp
    DbDataTicketHandler.cpp
    DbDataTokenHandler.cpp
    DbDataOwnershipHandler.cpp
    DbDataSecureDlcHandler.cpp
)

set(DBDATA_HEADERS
    DbDataLoader.hpp
    DbDataExports.hpp
    DbDataInitHandler.hpp
    DbDataConfigReader.hpp
    DbDataStateManager.hpp
    DbDataTicketHandler.hpp
    DbDataTokenHandler.hpp
    DbDataOwnershipHandler.hpp
    DbDataSecureDlcHandler.hpp
)

add_library(EmuDbData SHARED ${DBDATA_SOURCES} ${DBDATA_HEADERS})
target_link_libraries(EmuDbData PRIVATE LibUbi)
target_include_directories(EmuDbData PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    set_target_properties(EmuDbData PROPERTIES
        SUFFIX ".dll"
        PREFIX ""
        OUTPUT_NAME "dbdata"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin/DbData"
    )
endif()
