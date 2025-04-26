project(test_queue LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("../../../src/DataStructures/Queue/")

add_executable(QueueCtors QueueCtors.cpp)
add_test(NAME QueueCtors COMMAND QueueCtors)

add_executable(QueueGrow QueueGrow.cpp)
add_test(NAME QueueGrow COMMAND QueueGrow)

add_executable(QueueShrink QueueShrink.cpp)
add_test(NAME QueueShrink COMMAND QueueShrink)

add_executable(QueueGet QueueGet.cpp)
add_test(NAME QueueGet COMMAND QueueGet)

add_executable(QueueSet QueueSet.cpp)
add_test(NAME QueueSet COMMAND QueueSet)

add_executable(QueueOperators QueueOperators.cpp)
add_test(NAME QueueOperators COMMAND QueueOperators)
