aux_source_directory(./ regexpsrc)


add_executable(regexp ${regexpsrc})
target_link_libraries(regexp lua luabind)