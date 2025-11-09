
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/tests/)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/tests)

add_executable(array_test array_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(array_test PRIVATE dsa_testing)
add_test(NAME array_test COMMAND array_test)

add_executable(array_operators_test array_operators_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(array_operators_test PRIVATE dsa_testing)
add_test(NAME array_operators_test COMMAND array_operators_test)

add_executable(array_binding_test array_binding_test.cpp ${SRC_DIR}/common.cpp)
target_link_libraries(array_binding_test PRIVATE dsa_testing)
add_test(NAME array_binding_test COMMAND array_binding_test)
