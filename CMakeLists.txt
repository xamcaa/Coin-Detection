cmake_minimum_required(VERSION 2.8)
project(coins)

# find OpenCV
find_package(OpenCV REQUIRED)
set(LIBRARY_DEPS ${OpenCV_LIBS})

# INCLUDE
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/testdata")

file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.hpp")
add_executable(main ${srcs} ${hdrs})
target_link_libraries(main ${LIBRARY_DEPS})

# messages
message( STATUS "   OpenCV build path:    ${OpenCV_DIR}")
