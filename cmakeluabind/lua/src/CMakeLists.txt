SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

aux_source_directory(./ luasrc)


add_definitions(-DLUA_BUILD_AS_DLL)
add_library(lua SHARED ${luasrc})
add_executable(luaexec ${luasrc})