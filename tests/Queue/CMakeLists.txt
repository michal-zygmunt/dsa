
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/tests/)

add_executable(QueueCtorsTest QueueCtorsTest.cpp)
target_link_libraries(QueueCtorsTest PRIVATE dsa_testing)
add_test(NAME QueueCtorsTest COMMAND QueueCtorsTest)

add_executable(QueueGrowTest QueueGrowTest.cpp)
target_link_libraries(QueueGrowTest PRIVATE dsa_testing)
add_test(NAME QueueGrowTest COMMAND QueueGrowTest)

add_executable(QueueShrinkTest QueueShrinkTest.cpp)
target_link_libraries(QueueShrinkTest PRIVATE dsa_testing)
add_test(NAME QueueShrinkTest COMMAND QueueShrinkTest)

add_executable(QueueGetTest QueueGetTest.cpp)
target_link_libraries(QueueGetTest PRIVATE dsa_testing)
add_test(NAME QueueGetTest COMMAND QueueGetTest)

add_executable(QueueSetTest QueueSetTest.cpp)
target_link_libraries(QueueSetTest PRIVATE dsa_testing)
add_test(NAME QueueSetTest COMMAND QueueSetTest)

add_executable(QueueOperatorsTest QueueOperatorsTest.cpp)
target_link_libraries(QueueOperatorsTest PRIVATE dsa_testing)
add_test(NAME QueueOperatorsTest COMMAND QueueOperatorsTest)
