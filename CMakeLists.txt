cmake_minimum_required(VERSION 3.27)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

project(DataStuff VERSION 0.0)
add_library(DataStuff 
	src/BHeap.c
    src/BinarySearchTree.c 
    src/CmpFunc.c 
    src/EqFunc.c 
    src/HashTable.c 
    src/Heap.c 
    src/LinkedList.c 
    src/Stack.c
	src/Vector.c
)
target_include_directories(DataStuff PUBLIC "${PROJECT_SOURCE_DIR}/include/DataStuff/")
target_compile_options(DataStuff PUBLIC -std=c17 -g -Wpedantic -Wall -Wextra
	-Werror=return-type 
	-Werror=implicit-function-declaration 
	-Werror=implicit-int
	-Werror=sign-compare
	-Werror=stringop-overread
	-Werror=incompatible-pointer-types
	-Werror=int-conversion
	-Werror=format
)

project(DataStuffTest)
add_executable(DataStuffTest src/Test.c)
target_include_directories(DataStuffTest PUBLIC "${PROJECT_SOURCE_DIR}/include/DataStuff/")
target_link_libraries(DataStuffTest PUBLIC DataStuff)
target_compile_options(DataStuffTest PUBLIC ${COMPILE_OPTIONS_GCC})
