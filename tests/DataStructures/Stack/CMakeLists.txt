project(test_stack LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("../../../src/DataStructures/Stack/")
include_directories("../")

add_executable(StackCtorsTest StackCtorsTest.cpp)
add_test(NAME StackCtorsTest COMMAND StackCtorsTest)

add_executable(StackGrowTest StackGrowTest.cpp)
add_test(NAME StackGrowTest COMMAND StackGrowTest)

add_executable(StackShrinkTest StackShrinkTest.cpp)
add_test(NAME StackShrinkTest COMMAND StackShrinkTest)

add_executable(StackGetTest StackGetTest.cpp)
add_test(NAME StackGetTest COMMAND StackGetTest)

add_executable(StackSetTest StackSetTest.cpp)
add_test(NAME StackSetTest COMMAND StackSetTest)

add_executable(StackOperatorsTest StackOperatorsTest.cpp)
add_test(NAME StackOperatorsTest COMMAND StackOperatorsTest)
