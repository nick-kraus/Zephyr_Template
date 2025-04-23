cmake_minimum_required(VERSION 3.20.0)

# TEMPLATE_CONFIG: Set project name, used for firmware output filename.
set(PROJECT app)

# Add board name to firmware output filename.
set(CONFIG_KERNEL_BIN_NAME \"${PROJECT}-${BOARD}\" CACHE STRING "build output filename" FORCE)
# Add binary descriptors 'APP_VERSION_STRING' (based off 'VERSION' file) and 'APP_BUILD_VERSION'
# (based off 'git describe'). See 'zephyr/doc/services/binary_descriptors/index.rst' for
# additional information.
set(CONFIG_BINDESC "y" CACHE STRING "use binary descriptors")
set(CONFIG_BINDESC_DEFINE "y" CACHE STRING "define binary descriptors")
set(CONFIG_BINDESC_DEFINE_VERSION "y" CACHE STRING "define version binary descriptors")
set(CONFIG_BINDESC_APP_VERSION_STRING "y" CACHE STRING "version file string binary descriptor")
set(CONFIG_BINDESC_APP_BUILD_VERSION "y" CACHE STRING "git describe string binary descriptor")

find_package(Zephyr REQUIRED HINTS "${CMAKE_CURRENT_SOURCE_DIR}/zephyr")
project(${PROJECT} LANGUAGES C)

target_sources(${PROJECT} PRIVATE
    "src/main.c"
)

target_include_directories(${PROJECT} PRIVATE
    "src"
)
