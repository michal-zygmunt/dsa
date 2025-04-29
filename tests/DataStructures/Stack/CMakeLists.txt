project(test_stack LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("../../../src/DataStructures/Stack/")

add_executable(StackCtors StackCtors.cpp)
add_test(NAME StackCtors COMMAND StackCtors)

add_executable(StackGrow StackGrow.cpp)
add_test(NAME StackGrow COMMAND StackGrow)

add_executable(StackShrink StackShrink.cpp)
add_test(NAME StackShrink COMMAND StackShrink)

add_executable(StackGet StackGet.cpp)
add_test(NAME StackGet COMMAND StackGet)

add_executable(StackSet StackSet.cpp)
add_test(NAME StackSet COMMAND StackSet)

add_executable(StackOperators StackOperators.cpp)
add_test(NAME StackOperators COMMAND StackOperators)
