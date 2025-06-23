project(test_queue LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("../../../src/DataStructures/Queue/")
include_directories("../")

add_executable(QueueCtorsTest QueueCtorsTest.cpp)
add_test(NAME QueueCtorsTest COMMAND QueueCtorsTest)

add_executable(QueueGrowTest QueueGrowTest.cpp)
add_test(NAME QueueGrowTest COMMAND QueueGrowTest)

add_executable(QueueShrinkTest QueueShrinkTest.cpp)
add_test(NAME QueueShrinkTest COMMAND QueueShrinkTest)

add_executable(QueueGetTest QueueGetTest.cpp)
add_test(NAME QueueGetTest COMMAND QueueGetTest)

add_executable(QueueSetTest QueueSetTest.cpp)
add_test(NAME QueueSetTest COMMAND QueueSetTest)

add_executable(QueueOperatorsTest QueueOperatorsTest.cpp)
add_test(NAME QueueOperatorsTest COMMAND QueueOperatorsTest)
