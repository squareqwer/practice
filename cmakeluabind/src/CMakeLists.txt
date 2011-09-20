SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

aux_source_directory(./ luabindsrc)

add_library(luabind STATIC ${luabindsrc})