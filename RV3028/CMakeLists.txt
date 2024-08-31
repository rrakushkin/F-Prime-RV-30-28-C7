# CMake minimum version
cmake_minimum_required(VERSION 3.13)

# F Prime project setup
project(RV3028 LANGUAGES C CXX)

# Set the path to the Pico SDK
# Replace the following path with the actual path where you cloned the Pico SDK
set(PICO_SDK_PATH "/mnt/c/Users/rache/pico-sdk")

# Include the Pico SDK in the build
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Initialize the Pico SDK
pico_sdk_init()

# Set the source files for the component
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/RV3028.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/RV3028.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/RV3028.hpp"
)

# Uncomment and add any modules that this component depends on.
# set(MOD_DEPS
#     Add your dependencies here
# )

# Define target for the RV3028 component
add_fprime_module(
  RV3028
  SOURCES ${SOURCE_FILES}
)

# Link the necessary Pico SDK libraries
target_link_libraries(RV3028
  pico_stdlib
  hardware_i2c
)

# Register the F Prime module
register_fprime_module()
