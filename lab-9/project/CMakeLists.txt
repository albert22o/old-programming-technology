cmake_minimum_required(VERSION 3.10)
project(TPolyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(main src/main.cpp)
add_executable(tests tests/PolyTests.cpp)
# headers-only implementation: no need to add UPoly.cpp; if you create UPoly.cpp, add it to targets.
