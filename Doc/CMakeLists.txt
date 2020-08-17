cmake_minimum_required (VERSION 3.0)
# Name our project
project (blink_example)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

FILE(GLOB SRC_FILES main.c)
add_executable(blink_example ${SRC_FILES})
# Link the pre-compiled wiringPi library to the executable we just declared 
target_link_libraries(blink_example ${CMAKE_THREAD_LIBS_INIT})
