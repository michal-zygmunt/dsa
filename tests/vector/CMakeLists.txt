
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/tests/)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/tests)

add_executable(vector_ctors_test vector_ctors_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(vector_ctors_test PRIVATE dsa_testing)
add_test(NAME vector_ctors_test COMMAND vector_ctors_test)

add_executable(vector_grow_test vector_grow_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(vector_grow_test PRIVATE dsa_testing)
add_test(NAME vector_grow_test COMMAND vector_grow_test)

add_executable(vector_resize_test vector_resize_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(vector_resize_test PRIVATE dsa_testing)
add_test(NAME vector_resize_test COMMAND vector_resize_test)

add_executable(vector_set_test vector_set_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(vector_set_test PRIVATE dsa_testing)
add_test(NAME vector_set_test COMMAND vector_set_test)

add_executable(vector_shrink_test vector_shrink_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(vector_shrink_test PRIVATE dsa_testing)
add_test(NAME vector_shrink_test COMMAND vector_shrink_test)

add_executable(vector_swap_test vector_swap_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(vector_swap_test PRIVATE dsa_testing)
add_test(NAME vector_swap_test COMMAND vector_swap_test)

add_executable(vector_operators_test vector_operators_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(vector_operators_test PRIVATE dsa_testing)
add_test(NAME vector_operators_test COMMAND vector_operators_test)

add_executable(vector_itors_test vector_itors_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(vector_itors_test PRIVATE dsa_testing)
add_test(NAME vector_itors_test COMMAND vector_itors_test)

add_executable(vector_ranges_test vector_ranges_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(vector_ranges_test PRIVATE dsa_testing)
add_test(NAME vector_ranges_test COMMAND vector_ranges_test)
