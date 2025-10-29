
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/tests/)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/tests)

add_executable(forward_list_ctors_test forward_list_ctors_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(forward_list_ctors_test PRIVATE dsa_testing)
add_test(NAME forward_list_ctors_test COMMAND forward_list_ctors_test)

add_executable(forward_list_grow_test forward_list_grow_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(forward_list_grow_test PRIVATE dsa_testing)
add_test(NAME forward_list_grow_test COMMAND forward_list_grow_test)

add_executable(forward_list_shrink_test forward_list_shrink_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(forward_list_shrink_test PRIVATE dsa_testing)
add_test(NAME forward_list_shrink_test COMMAND forward_list_shrink_test)

add_executable(forward_list_get_test forward_list_get_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(forward_list_get_test PRIVATE dsa_testing)
add_test(NAME forward_list_get_test COMMAND forward_list_get_test)

add_executable(forward_list_set_test forward_list_set_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(forward_list_set_test PRIVATE dsa_testing)
add_test(NAME forward_list_set_test COMMAND forward_list_set_test)

add_executable(forward_list_reverse_test forward_list_reverse_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(forward_list_reverse_test PRIVATE dsa_testing)
add_test(NAME forward_list_reverse_test COMMAND forward_list_reverse_test)

add_executable(forward_list_operators_test forward_list_operators_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(forward_list_operators_test PRIVATE dsa_testing)
add_test(NAME forward_list_operators_test COMMAND forward_list_operators_test)

add_executable(forward_list_swap_test forward_list_swap_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(forward_list_swap_test PRIVATE dsa_testing)
add_test(NAME forward_list_swap_test COMMAND forward_list_swap_test)

add_executable(forward_list_merge_test forward_list_merge_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(forward_list_merge_test PRIVATE dsa_testing)
add_test(NAME forward_list_merge_test COMMAND forward_list_merge_test)

add_executable(forward_list_resize_test forward_list_resize_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(forward_list_resize_test PRIVATE dsa_testing)
add_test(NAME forward_list_resize_test COMMAND forward_list_resize_test)

add_executable(forward_list_unique_test forward_list_unique_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(forward_list_unique_test PRIVATE dsa_testing)
add_test(NAME forward_list_unique_test COMMAND forward_list_unique_test)

add_executable(forward_list_splice_test forward_list_splice_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(forward_list_splice_test PRIVATE dsa_testing)
add_test(NAME forward_list_splice_test COMMAND forward_list_splice_test)

add_executable(forward_list_itors_test forward_list_itors_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(forward_list_itors_test PRIVATE dsa_testing)
add_test(NAME forward_list_itors_test COMMAND forward_list_itors_test)

add_executable(forward_list_ranges_test forward_list_ranges_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(forward_list_ranges_test PRIVATE dsa_testing)
add_test(NAME forward_list_ranges_test COMMAND forward_list_ranges_test)
