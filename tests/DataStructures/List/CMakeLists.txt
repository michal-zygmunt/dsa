project(test_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("../../../src/DataStructures/List/")

add_executable(ListCtors ListCtors.cpp)
add_test(NAME ListCtors COMMAND ListCtors)

add_executable(ListGrow ListGrow.cpp)
add_test(NAME ListGrow COMMAND ListGrow)

add_executable(ListShrink ListShrink.cpp)
add_test(NAME ListShrink COMMAND ListShrink)

add_executable(ListGet ListGet.cpp)
add_test(NAME ListGet COMMAND ListGet)

add_executable(ListSet ListSet.cpp)
add_test(NAME ListSet COMMAND ListSet)

add_executable(ListReverse ListReverse.cpp)
add_test(NAME ListReverse COMMAND ListReverse)

add_executable(ListOperators ListOperators.cpp)
add_test(NAME ListOperators COMMAND ListOperators)

add_executable(ListSwap ListSwap.cpp)
add_test(NAME ListSwap COMMAND ListSwap)

add_executable(ListMerge ListMerge.cpp)
add_test(NAME ListMerge COMMAND ListMerge)

add_executable(ListResize ListResize.cpp)
add_test(NAME ListResize COMMAND ListResize)

add_executable(ListUnique ListUnique.cpp)
add_test(NAME ListUnique COMMAND ListUnique)

add_executable(ListSplice ListSplice.cpp)
add_test(NAME ListSplice COMMAND ListSplice)

add_executable(ListItors ListItors.cpp)
add_test(NAME ListItors COMMAND ListItors)
