cmake_minimum_required(VERSION 2.8)
project(coins)

# find OpenCV
find_package(OpenCV REQUIRED)
set(LIBRARY_DEPS ${OpenCV_LIBS})

set(SOURCES main.cpp)
add_executable(main ${SOURCES})
target_link_libraries(main ${LIBRARY_DEPS})

# messages
message( STATUS "   OpenCV build path:    ${OpenCV_DIR}")
