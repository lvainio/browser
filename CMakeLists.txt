cmake_minimum_required(VERSION 4.0)

project(browser)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(browser 
    src/main.cpp
    src/url.cpp
)