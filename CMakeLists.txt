cmake_minimum_required(VERSION 4.0)

project(browser)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(CURL REQUIRED)

add_executable(browser 
    src/main.cpp
    src/url.cpp
)

target_link_libraries(browser CURL::libcurl)