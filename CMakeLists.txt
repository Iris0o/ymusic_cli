cmake_minimum_required(VERSION 4.0)
include(FetchContent)
project(ymusic_cli)

set(CMAKE_CXX_STANDARD 23)

# httplib
FetchContent_Declare(httplib
        GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
        GIT_TAG v0.21.0)
FetchContent_MakeAvailable(httplib)

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

add_executable(ymusic_cli main.cpp)

target_link_libraries(ymusic_cli PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(ymusic_cli
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom)

target_link_libraries(ymusic_cli
        PRIVATE httplib::httplib)

target_link_libraries(ymusic_cli PRIVATE miniaudio)