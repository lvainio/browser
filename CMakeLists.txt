cmake_minimum_required(VERSION 4.0)

project(seal)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(CURL REQUIRED)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.12
)
FetchContent_MakeAvailable(doctest)

add_library(seal_core
    src/url.cpp
)
target_include_directories(seal_core PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_executable(seal
    src/main.cpp
)
target_link_libraries(seal PRIVATE seal_core CURL::libcurl Qt6::Widgets)

add_executable(tests
    tests/test_url.cpp
)
target_link_libraries(tests PRIVATE seal_core doctest::doctest)

enable_testing()
add_test(NAME MyUnitTests COMMAND tests)
