cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_BUILD_TYPE Debug)

MESSAGE("${CMAKE_C_FLAGS}")

# Check "echo | gcc -E -Wp,-v -" if you need to set these. For me (Arch Linux) it was
# neccessary...for some reason. Not really sure why :/
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/include/glib-2.0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/lib/glib-2.0/include")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/include/dbus-1.0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/lib/dbus-1.0/include")

# Set the C version we want to talk
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

# Create a library with our file
add_library(libgrabby SHARED lib/grabby.c)
target_include_directories(libgrabby PUBLIC "include")
target_include_directories(libgrabby PRIVATE "lib")
target_link_libraries(libgrabby glib-2.0 dbus-1 dbus-glib-1)

# Create a simple test binary
add_executable(grabbytest test.c)
target_link_libraries(grabbytest libgrabby)
