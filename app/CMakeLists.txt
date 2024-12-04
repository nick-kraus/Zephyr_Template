cmake_minimum_required(VERSION 3.20.0)

# set project name, used for output file firmware name
set(PROJECT app)

find_package(Zephyr REQUIRED HINTS "${CMAKE_CURRENT_SOURCE_DIR}/zephyr")
project(${PROJECT} LANGUAGES C)

target_sources(${PROJECT} PRIVATE
    "src/main.c"
)

target_include_directories(${PROJECT} PRIVATE
    "src"
)
