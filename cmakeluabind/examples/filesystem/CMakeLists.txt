aux_source_directory(./ filesystemsrc)


add_executable(filesystem ${filesystemsrc})
target_link_libraries(filesystem lua luabind)