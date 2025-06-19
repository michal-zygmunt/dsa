project(test_forward_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("../../../src/DataStructures/ForwardList/")
include_directories("../")

add_executable(ForwardListCtors ForwardListCtors.cpp)
add_test(NAME ForwardListCtors COMMAND ForwardListCtors)

add_executable(ForwardListGrow ForwardListGrow.cpp)
add_test(NAME ForwardListGrow COMMAND ForwardListGrow)

add_executable(ForwardListShrink ForwardListShrink.cpp)
add_test(NAME ForwardListShrink COMMAND ForwardListShrink)

add_executable(ForwardListGet ForwardListGet.cpp)
add_test(NAME ForwardListGet COMMAND ForwardListGet)

add_executable(ForwardListSet ForwardListSet.cpp)
add_test(NAME ForwardListSet COMMAND ForwardListSet)

add_executable(ForwardListReverse ForwardListReverse.cpp)
add_test(NAME ForwardListReverse COMMAND ForwardListReverse)

add_executable(ForwardListOperators ForwardListOperators.cpp)
add_test(NAME ForwardListOperators COMMAND ForwardListOperators)

add_executable(ForwardListSwap ForwardListSwap.cpp)
add_test(NAME ForwardListSwap COMMAND ForwardListSwap)

add_executable(ForwardListMerge ForwardListMerge.cpp)
add_test(NAME ForwardListMerge COMMAND ForwardListMerge)

add_executable(ForwardListResize ForwardListResize.cpp)
add_test(NAME ForwardListResize COMMAND ForwardListResize)

add_executable(ForwardListUnique ForwardListUnique.cpp)
add_test(NAME ForwardListUnique COMMAND ForwardListUnique)

add_executable(ForwardListSplice ForwardListSplice.cpp)
add_test(NAME ForwardListSplice COMMAND ForwardListSplice)

add_executable(ForwardListItors ForwardListItors.cpp)
add_test(NAME ForwardListItors COMMAND ForwardListItors)
