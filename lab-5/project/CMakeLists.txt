cmake_minimum_required(VERSION 3.10)
project(TPNumberProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(tpnumber STATIC src/TPNumber.cpp)
target_include_directories(tpnumber PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(tests tests/TPNumberTests.cpp)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tests PRIVATE tpnumber)

enable_testing()
add_test(NAME TPNumberTests COMMAND tests)
