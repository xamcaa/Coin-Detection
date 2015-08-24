cmake_minimum_required(VERSION 2.8)
project(coins)

# find OpenCV
find_package(OpenCV REQUIRED)
set(LIBRARY_DEPS ${OpenCV_LIBS})

set(SOURCES main.cpp)
add_executable(main ${SOURCES})

# messages
message( STATUS "   OpenCV build path:    ${OpenCV_DIR}")
