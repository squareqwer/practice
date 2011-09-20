aux_source_directory(./ hello_worldsrc)


add_library(hello_world MODULE ${hello_worldsrc})
target_link_libraries(hello_world lua luabind)