project(test_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("../../../src/DataStructures/List/")

add_executable(ListCtors ListCtors.cpp)
add_test(NAME ListCtors COMMAND ListCtors)

add_executable(ListGrow ListGrow.cpp)
add_test(NAME ListGrow COMMAND ListGrow)

add_executable(ListShrink ListShrink.cpp)
add_test(NAME ListShrink COMMAND ListShrink)

add_executable(ListGet ListGet.cpp)
add_test(NAME ListGet COMMAND ListGet)

add_executable(ListSet ListSet.cpp)
add_test(NAME ListSet COMMAND ListSet)

add_executable(ListReverse ListReverse.cpp)
add_test(NAME ListReverse COMMAND ListReverse)

add_executable(ListOperators ListOperators.cpp)
add_test(NAME ListOperators COMMAND ListOperators)
