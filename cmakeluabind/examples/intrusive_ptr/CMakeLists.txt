aux_source_directory(./ intrusive_ptrsrc)


add_executable(intrusive_ptr ${intrusive_ptrsrc})
target_link_libraries(intrusive_ptr lua luabind)