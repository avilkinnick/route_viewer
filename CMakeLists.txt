cmake_minimum_required(VERSION 3.30)

project(route_viewer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
find_package(SDL2 REQUIRED)

add_executable(route_viewer
    src/Application.cpp
    src/logging.cpp
    src/main.cpp
    src/SdlInstance.cpp
    src/Window.cpp
)

target_link_libraries(route_viewer PRIVATE
    Vulkan::Vulkan
    SDL2::SDL2
    SDL2::SDL2main
)

target_include_directories(route_viewer PRIVATE include)
