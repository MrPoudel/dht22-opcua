cmake_minimum_required (VERSION 3.7)

project (dht22)

include_directories (${PROJECT_SOURCE_DIR}/include)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(WiringPi REQUIRED)
find_package(Threads REQUIRED)

# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS}) 
add_library (open62541 src/open62541.c)
add_library (gpio_read src/gpio_read.c)
add_executable (dht22_server dht22.c)
target_link_libraries (dht22_server  ${CMAKE_THREAD_LIBS_INIT} ${WIRINGPI_LIBRARIES} open62541 gpio_read) 


