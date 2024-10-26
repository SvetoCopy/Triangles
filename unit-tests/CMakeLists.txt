cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(triangles VERSION 1.0)

file(GLOB_RECURSE SRC_FILES ../src/*.cpp)

add_executable(INTERVAL_TEST IntervalsTest.cpp ${SRC_FILES})
target_include_directories(INTERVAL_TEST PUBLIC ../inc)
target_link_libraries(INTERVAL_TEST gtest gmock pthread)

add_executable(LINE_TEST LineTest.cpp ${SRC_FILES})
target_include_directories(LINE_TEST PUBLIC ../inc)
target_link_libraries(LINE_TEST gtest gmock pthread)

add_executable(PLANE_TEST PlaneTest.cpp ${SRC_FILES})
target_include_directories(PLANE_TEST PUBLIC ../inc)
target_link_libraries(PLANE_TEST gtest gmock pthread)

add_executable(POINT_TEST PointTest.cpp ${SRC_FILES})
target_include_directories(POINT_TEST PUBLIC ../inc)
target_link_libraries(POINT_TEST gtest gmock pthread)

add_executable(TRIANGLE_TEST TriangleTest.cpp ${SRC_FILES})
target_include_directories(TRIANGLE_TEST PUBLIC ../inc)
target_link_libraries(TRIANGLE_TEST gtest gmock pthread)

add_executable(VECTOR_TEST VectorTest.cpp ${SRC_FILES})
target_include_directories(VECTOR_TEST PUBLIC ../inc)
target_link_libraries(VECTOR_TEST gtest gmock pthread)