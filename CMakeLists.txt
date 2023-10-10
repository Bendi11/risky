cmake_minimum_required(VERSION 3.14)

project(
    risky
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(
    SRC
    "src/main.cpp"
    "src/machine.cpp"
)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "./include/")
