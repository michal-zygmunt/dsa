
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/tests/)

add_executable(StackCtorsTest StackCtorsTest.cpp)
target_link_libraries(StackCtorsTest PRIVATE dsa_testing)
add_test(NAME StackCtorsTest COMMAND StackCtorsTest)

add_executable(StackGrowTest StackGrowTest.cpp)
target_link_libraries(StackGrowTest PRIVATE dsa_testing)
add_test(NAME StackGrowTest COMMAND StackGrowTest)

add_executable(StackShrinkTest StackShrinkTest.cpp)
target_link_libraries(StackShrinkTest PRIVATE dsa_testing)
add_test(NAME StackShrinkTest COMMAND StackShrinkTest)

add_executable(StackGetTest StackGetTest.cpp)
target_link_libraries(StackGetTest PRIVATE dsa_testing)
add_test(NAME StackGetTest COMMAND StackGetTest)

add_executable(StackSetTest StackSetTest.cpp)
target_link_libraries(StackSetTest PRIVATE dsa_testing)
add_test(NAME StackSetTest COMMAND StackSetTest)

add_executable(StackOperatorsTest StackOperatorsTest.cpp)
target_link_libraries(StackOperatorsTest PRIVATE dsa_testing)
add_test(NAME StackOperatorsTest COMMAND StackOperatorsTest)
