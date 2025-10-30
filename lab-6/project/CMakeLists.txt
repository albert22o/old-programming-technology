cmake_minimum_required(VERSION 3.5)
project(ComplexEditorTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(UEditor STATIC src/UEditor.cpp)
target_include_directories(UEditor PUBLIC include)

add_executable(tests tests/EditorTests.cpp)
target_link_libraries(tests PRIVATE UEditor)
