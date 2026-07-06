
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/tests/)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/tests)

add_executable(priority_queue_ctors_test priority_queue_ctors_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(priority_queue_ctors_test PRIVATE dsa_testing)
add_test(NAME priority_queue_ctors_test COMMAND priority_queue_ctors_test)

add_executable(priority_queue_test priority_queue_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(priority_queue_test PRIVATE dsa_testing)
add_test(NAME priority_queue_test COMMAND priority_queue_test)

add_executable(priority_queue_swap_test priority_queue_swap_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(priority_queue_swap_test PRIVATE dsa_testing)
add_test(NAME priority_queue_swap_test COMMAND priority_queue_swap_test)
