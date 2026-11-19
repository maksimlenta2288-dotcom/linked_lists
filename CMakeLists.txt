cmake_minimum_required(VERSION 3.20)
project(Linked_Lists LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)
include_directories(include)

set(LIST_SOURCES src/singly_list.cpp src/doubly_list.cpp src/name_search.cpp src/planets.cpp src/tasks.cpp)

add_executable(linked_lists src/main.cpp ${LIST_SOURCES})

enable_testing()
add_executable(manual_tests tests/manual_tests.cpp ${LIST_SOURCES})
add_test(NAME manual_tests COMMAND manual_tests)
