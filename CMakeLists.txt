cmake_minimum_required(VERSION 4.0)
include(FetchContent)
project(ymusic_cli)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# cpr
FetchContent_Declare(cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1.11.2)
FetchContent_MakeAvailable(cpr)

# miniaudio
add_library(miniaudio INTERFACE)
target_include_directories(miniaudio INTERFACE third_party/miniaudio)

# nlohmann/json
FetchContent_Declare(json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

# ftxui
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
        GIT_TAG v6.1.9)
FetchContent_MakeAvailable(ftxui)

add_executable(ymusic_cli main.cpp
        src/models/schemas.hpp
        src/ui/search.hpp)

target_link_libraries(ymusic_cli PRIVATE stdc++exp)
target_link_libraries(ymusic_cli PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(ymusic_cli
        PRIVATE ftxui::component
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom)

target_link_libraries(ymusic_cli
        PRIVATE cpr::cpr)

target_link_libraries(ymusic_cli PRIVATE miniaudio)

add_custom_command(TARGET ymusic_cli POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:ymusic_cli>
        $<TARGET_FILE_DIR:ymusic_cli>
        COMMAND_EXPAND_LISTS
)