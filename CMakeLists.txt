cmake_minimum_required(VERSION 4.0)

project(seal)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(CURL REQUIRED)

add_executable(browser 
    src/main.cpp
    src/url.cpp
)

target_link_libraries(browser CURL::libcurl)