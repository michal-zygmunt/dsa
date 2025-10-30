
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/tests/)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/tests)

add_executable(list_ctors_test list_ctors_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(list_ctors_test PRIVATE dsa_testing)
add_test(NAME list_ctors_test COMMAND list_ctors_test)

add_executable(list_grow_test list_grow_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(list_grow_test PRIVATE dsa_testing)
add_test(NAME list_grow_test COMMAND list_grow_test)

add_executable(list_shrink_test list_shrink_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(list_shrink_test PRIVATE dsa_testing)
add_test(NAME list_shrink_test COMMAND list_shrink_test)

add_executable(list_get_test list_get_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(list_get_test PRIVATE dsa_testing)
add_test(NAME list_get_test COMMAND list_get_test)

add_executable(list_set_test list_set_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(list_set_test PRIVATE dsa_testing)
add_test(NAME list_set_test COMMAND list_set_test)

add_executable(list_reverse_test list_reverse_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(list_reverse_test PRIVATE dsa_testing)
add_test(NAME list_reverse_test COMMAND list_reverse_test)

add_executable(list_operators_test list_operators_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(list_operators_test PRIVATE dsa_testing)
add_test(NAME list_operators_test COMMAND list_operators_test)

add_executable(list_swap_test list_swap_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(list_swap_test PRIVATE dsa_testing)
add_test(NAME list_swap_test COMMAND list_swap_test)

add_executable(list_merge_test list_merge_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(list_merge_test PRIVATE dsa_testing)
add_test(NAME list_merge_test COMMAND list_merge_test)

add_executable(list_resize_test list_resize_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(list_resize_test PRIVATE dsa_testing)
add_test(NAME list_resize_test COMMAND list_resize_test)

add_executable(list_unique_test list_unique_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(list_unique_test PRIVATE dsa_testing)
add_test(NAME list_unique_test COMMAND list_unique_test)

add_executable(list_splice_test list_splice_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(list_splice_test PRIVATE dsa_testing)
add_test(NAME list_splice_test COMMAND list_splice_test)

add_executable(list_itors_test list_itors_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(list_itors_test PRIVATE dsa_testing)
add_test(NAME list_itors_test COMMAND list_itors_test)

add_executable(list_ranges_test list_ranges_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(list_ranges_test PRIVATE dsa_testing)
add_test(NAME list_ranges_test COMMAND list_ranges_test)
