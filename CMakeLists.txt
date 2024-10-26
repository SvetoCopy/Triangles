cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(triangles VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(TRIANGLES main.cpp ${SRC_FILES})
target_include_directories(TRIANGLES PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(TRIANGLES_TEST tests.cpp ${SRC_FILES})
target_include_directories(TRIANGLES_TEST PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(TRIANGLES_TEST gtest gmock pthread)