project(test_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("../../../src/DataStructures/List/")
include_directories("../")

add_executable(ListCtorsTest ListCtorsTest.cpp)
add_test(NAME ListCtorsTest COMMAND ListCtorsTest)

add_executable(ListGrowTest ListGrowTest.cpp)
add_test(NAME ListGrowTest COMMAND ListGrowTest)

add_executable(ListShrinkTest ListShrinkTest.cpp)
add_test(NAME ListShrinkTest COMMAND ListShrinkTest)

add_executable(ListGetTest ListGetTest.cpp)
add_test(NAME ListGetTest COMMAND ListGetTest)

add_executable(ListSetTest ListSetTest.cpp)
add_test(NAME ListSetTest COMMAND ListSetTest)

add_executable(ListReverseTest ListReverseTest.cpp)
add_test(NAME ListReverseTest COMMAND ListReverseTest)

add_executable(ListOperatorsTest ListOperatorsTest.cpp)
add_test(NAME ListOperatorsTest COMMAND ListOperatorsTest)

add_executable(ListSwapTest ListSwapTest.cpp)
add_test(NAME ListSwapTest COMMAND ListSwapTest)

add_executable(ListMergeTest ListMergeTest.cpp)
add_test(NAME ListMergeTest COMMAND ListMergeTest)

add_executable(ListResizeTest ListResizeTest.cpp)
add_test(NAME ListResizeTest COMMAND ListResizeTest)

add_executable(ListUniqueTest ListUniqueTest.cpp)
add_test(NAME ListUniqueTest COMMAND ListUniqueTest)

add_executable(ListSpliceTest ListSpliceTest.cpp)
add_test(NAME ListSpliceTest COMMAND ListSpliceTest)

add_executable(ListItorsTest ListItorsTest.cpp)
add_test(NAME ListItorsTest COMMAND ListItorsTest)
