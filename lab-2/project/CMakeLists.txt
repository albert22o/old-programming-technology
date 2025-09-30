cmake_minimum_required(VERSION 3.14)
project(MyLibProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опция сборки (Debug по умолчанию)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# ---- библиотека mylib ----
add_library(mylib STATIC
    src/MyLib.cpp
)

target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ---- простые тесты (без внешних зависимостей) ----
add_executable(tests
    tests/MyLibTests.cpp
)

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tests PRIVATE mylib)

enable_testing()
add_test(NAME Tests COMMAND tests)
