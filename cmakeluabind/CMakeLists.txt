project(testcmake)
cmake_minimum_required(VERSION 2.8)

include_directories(
D:/boost/include/boost-1_47
./
lua/include
)
link_directories(
D:/boost/lib
)

add_subdirectory(lua)

add_subdirectory(src)

add_subdirectory(examples)

add_subdirectory(test)