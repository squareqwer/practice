aux_source_directory(./ glutsrc)


add_executable(glut ${glutsrc})
target_link_libraries(glut lua luabind)