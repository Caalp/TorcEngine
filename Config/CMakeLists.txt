set (FILES
  
  Build/collect_files.py
  Build/copy_dependency_list.py
  Build/create_editor_config_props.py
  Build/download_dependencies.py

  Build/CMake/cmake_configure.cmake
  Build/CMake/cmake_gfx_configure.cmake
  Build/CMake/cmake_utilities.cmake
  Build/CMake/cmake_wrappers.cmake

  generate_md5.py
)

add_custom_target(Config SOURCES ${FILES})
set_target_properties(Config PROPERTIES FOLDER Config)
te_source_group("${FILES}")
