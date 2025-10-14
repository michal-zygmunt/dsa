
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/tests/)

add_executable(stack_ctors_test stack_ctors_test.cpp)
target_link_libraries(stack_ctors_test PRIVATE dsa_testing)
add_test(NAME stack_ctors_test COMMAND stack_ctors_test)

add_executable(stack_grow_test stack_grow_test.cpp)
target_link_libraries(stack_grow_test PRIVATE dsa_testing)
add_test(NAME stack_grow_test COMMAND stack_grow_test)

add_executable(stack_shrink_test stack_shrink_test.cpp)
target_link_libraries(stack_shrink_test PRIVATE dsa_testing)
add_test(NAME stack_shrink_test COMMAND stack_shrink_test)

add_executable(stack_get_test stack_get_test.cpp)
target_link_libraries(stack_get_test PRIVATE dsa_testing)
add_test(NAME stack_get_test COMMAND stack_get_test)

add_executable(stack_set_test stack_set_test.cpp)
target_link_libraries(stack_set_test PRIVATE dsa_testing)
add_test(NAME stack_set_test COMMAND stack_set_test)

add_executable(stack_operators_test stack_operators_test.cpp)
target_link_libraries(stack_operators_test PRIVATE dsa_testing)
add_test(NAME stack_operators_test COMMAND stack_operators_test)
