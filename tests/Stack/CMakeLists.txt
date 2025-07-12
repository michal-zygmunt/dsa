project(test_stack LANGUAGES CXX)

include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/tests/)

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
