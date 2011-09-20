SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

aux_source_directory(./ luasrc)

add_library(lua STATIC ${luasrc})
add_executable(luaexec ${luasrc})