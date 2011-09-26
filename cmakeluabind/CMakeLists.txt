set(CMAKE_USER_MAKE_RULES_OVERRIDE
   ${CMAKE_CURRENT_SOURCE_DIR}/c_flag_overrides.cmake)
set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
   ${CMAKE_CURRENT_SOURCE_DIR}/cxx_flag_overrides.cmake)

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
