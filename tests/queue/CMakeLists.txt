
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/tests/)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/tests)

add_executable(queue_ctors_test queue_ctors_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(queue_ctors_test PRIVATE dsa_testing)
add_test(NAME queue_ctors_test COMMAND queue_ctors_test)

add_executable(queue_grow_test queue_grow_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(queue_grow_test PRIVATE dsa_testing)
add_test(NAME queue_grow_test COMMAND queue_grow_test)

add_executable(queue_shrink_test queue_shrink_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(queue_shrink_test PRIVATE dsa_testing)
add_test(NAME queue_shrink_test COMMAND queue_shrink_test)

add_executable(queue_get_test queue_get_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(queue_get_test PRIVATE dsa_testing)
add_test(NAME queue_get_test COMMAND queue_get_test)

add_executable(queue_set_test queue_set_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(queue_set_test PRIVATE dsa_testing)
add_test(NAME queue_set_test COMMAND queue_set_test)

add_executable(queue_operators_test queue_operators_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(queue_operators_test PRIVATE dsa_testing)
add_test(NAME queue_operators_test COMMAND queue_operators_test)
