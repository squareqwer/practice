aux_source_directory(./ any_convertersrc)


add_executable(any_converter ${any_convertersrc})
target_link_libraries(any_converter lua luabind)