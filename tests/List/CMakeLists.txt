
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/tests/)

add_executable(ListCtorsTest ListCtorsTest.cpp)
target_link_libraries(ListCtorsTest PRIVATE dsa_testing)
add_test(NAME ListCtorsTest COMMAND ListCtorsTest)

add_executable(ListGrowTest ListGrowTest.cpp)
target_link_libraries(ListGrowTest PRIVATE dsa_testing)
add_test(NAME ListGrowTest COMMAND ListGrowTest)

add_executable(ListShrinkTest ListShrinkTest.cpp)
target_link_libraries(ListShrinkTest PRIVATE dsa_testing)
add_test(NAME ListShrinkTest COMMAND ListShrinkTest)

add_executable(ListGetTest ListGetTest.cpp)
target_link_libraries(ListGetTest PRIVATE dsa_testing)
add_test(NAME ListGetTest COMMAND ListGetTest)

add_executable(ListSetTest ListSetTest.cpp)
target_link_libraries(ListSetTest PRIVATE dsa_testing)
add_test(NAME ListSetTest COMMAND ListSetTest)

add_executable(ListReverseTest ListReverseTest.cpp)
target_link_libraries(ListReverseTest PRIVATE dsa_testing)
add_test(NAME ListReverseTest COMMAND ListReverseTest)

add_executable(ListOperatorsTest ListOperatorsTest.cpp)
target_link_libraries(ListOperatorsTest PRIVATE dsa_testing)
add_test(NAME ListOperatorsTest COMMAND ListOperatorsTest)

add_executable(ListSwapTest ListSwapTest.cpp)
target_link_libraries(ListSwapTest PRIVATE dsa_testing)
add_test(NAME ListSwapTest COMMAND ListSwapTest)

add_executable(ListMergeTest ListMergeTest.cpp)
target_link_libraries(ListMergeTest PRIVATE dsa_testing)
add_test(NAME ListMergeTest COMMAND ListMergeTest)

add_executable(ListResizeTest ListResizeTest.cpp)
target_link_libraries(ListResizeTest PRIVATE dsa_testing)
add_test(NAME ListResizeTest COMMAND ListResizeTest)

add_executable(ListUniqueTest ListUniqueTest.cpp)
target_link_libraries(ListUniqueTest PRIVATE dsa_testing)
add_test(NAME ListUniqueTest COMMAND ListUniqueTest)

add_executable(ListSpliceTest ListSpliceTest.cpp)
target_link_libraries(ListSpliceTest PRIVATE dsa_testing)
add_test(NAME ListSpliceTest COMMAND ListSpliceTest)

add_executable(ListItorsTest ListItorsTest.cpp)
target_link_libraries(ListItorsTest PRIVATE dsa_testing)
add_test(NAME ListItorsTest COMMAND ListItorsTest)
