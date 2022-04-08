cmake_minimum_required(VERSION 3.22)

project(mcpixel VERSION 1.0.0 LANGUAGES CXX)

configure_file("${mcpixel_SOURCE_DIR}/cmake/version.h.in" "${mcpixel_BINARY_DIR}/include/mcpixel/version.h")

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MCPIXEL_LIBRARIES mcpixel CACHE INTERNAL "")

set(CPR_ENABLE_SSL ON)
set(CPR_FORCE_USE_SYSTEM_CURL ON)
set(CPR_BUILD_TESTS OFF)
set(JSON_Diagnostics ON) # Detailed JSON exceptions
set(JSON_BuildTests OFF)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 6ea2dec23c3df14ac3b27b7d2d6bbff0cb7ba1b0) # 1.8.1
FetchContent_Declare(nlohmann_json GIT_REPOSITORY https://github.com/nlohmann/json.git
                         GIT_TAG 4f8fba14066156b73f1189a2b8bd568bde5284c5) # 3.10.5
FetchContent_MakeAvailable(cpr nlohmann_json)

add_library(mcpixel SHARED
    mcpixel/hypixel_api.cpp
    mcpixel/hypixel_player.cpp
    mcpixel/logger.cpp
    mcpixel/minecraft_api.cpp
    mcpixel/minecraft_player.cpp
)

add_library(mcpixel::mcpixel ALIAS mcpixel)

target_include_directories(mcpixel PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(mcpixel PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR}
)

target_link_libraries(mcpixel PRIVATE cpr::cpr -lcpr)
target_link_libraries(mcpixel PRIVATE nlohmann_json::nlohmann_json)

install(TARGETS mcpixel cpr nlohmann_json
    EXPORT mcpixelTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT mcpixelTargets
    FILE mcpixelTargets.cmake
    NAMESPACE mcpixel::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mcpixel
)
