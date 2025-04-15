project(test_forward_list LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("../../../src/DataStructures/ForwardList/")

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
