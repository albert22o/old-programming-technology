cmake_minimum_required(VERSION 3.14)
project(MatrixProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(matrixlib STATIC src/Matrix.cpp)
target_include_directories(matrixlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(tests tests/MatrixTests.cpp)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tests PRIVATE matrixlib)

enable_testing()
add_test(NAME MatrixTests COMMAND tests)
