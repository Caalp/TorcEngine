function(te_print_list arg_list)
	foreach(line ${arg_list})
		message(STATUS "${line}")
	endforeach()
endfunction()

function(te_list_sub_dirs result startingDir)
  message(STATUS "GATHERING SUB-DIRECTORIES STARTING FROM ${startingDir}")
  file(GLOB subDirs RELATIVE ${startingDir} ${startingDir}/*)
  set(dirs "")
  #string(REPLACE "/" "\\" startingDir "${startingDir}")
  foreach(dir ${subDirs})
	if(IS_DIRECTORY ${startingDir}/${dir})
	# string(REPLACE "/" "\\" dir "${dir}")
	  list(APPEND dirs "${startingDir}${dir}")
	endif()
  endforeach()
  set(result "${dirs}") 
  set(${result} "${${result}}" PARENT_SCOPE)
  print_list("${result}")
endfunction()

# iterates and captures directories which contains CMakeLists.txt and adds them as sub-directory
# with that folder structure can be captured as it's structured
function(te_add_as_sub_directory current_dir)
  message(STATUS "GATHERING SUB-DIRECTORIES STARTING FROM ${current_dir}")
  file(GLOB subDirs RELATIVE ${current_dir} ${current_dir}/*)
  foreach(dir ${subDirs})
	if(IS_DIRECTORY ${current_dir}/${dir})
		# check if sub directory a valid one. Valid sub-directory means a directory with CMakeLists.txt
		if(EXISTS "${current_dir}/${dir}/CMakeLists.txt")
			message(STATUS "SUB-DIRECTORY ADDED ${current_dir}/${dir}.")
			add_subdirectory(${current_dir}/${dir})
		else()
			message(STATUS "[WARN] INVALID SUB-DIRECTORY ${current_dir}/${dir}. DIRECTORY IS NOT ADDED AS SUB_DIRECTORY!")
		endif()
	endif()
  endforeach()
endfunction()

function(te_add_target_sources_from_path target dir_to_add)
  message(STATUS "ADDING TARGET SOURCES TO ${target} STARTING FROM ${dir_to_add}")
  file(GLOB dir_content RELATIVE ${dir_to_add} ${dir_to_add}/*)
  set(elems "")

  foreach(elem ${dir_content})
    get_filename_component(ABSOLUTE_PATH "${dir_to_add}/${elem}" ABSOLUTE)
    list(APPEND elems "${ABSOLUTE_PATH}")
  endforeach()

  target_sources(${target} PRIVATE "${elems}")
  message(STATUS "Content of the directory ${dir_to_add}")
  print_list("${elems}")
endfunction()

# this function would add headers as PUBLIC, and cpp files as PRIVATE to the target
function(te_set_target_sources target_proj from_path)
message(STATUS "SETTING TARGET SOURCES  FOR ${target_proj} STARTING IN ${from_path}")
set(source_files "")
set(header_files "")
file(GLOB subDirs RELATIVE ${from_path} ${from_path}/*)
# create list of files
foreach(elem ${subDirs})
	if(EXISTS ${from_path}/${elem})
		if("${elem}" MATCHES ".*\\.cpp")
			message(STATUS "SOURCE FILE ADDED ${from_path}/${elem}")
			list(APPEND source_files "${from_path}/${elem}")
		elseif("${elem}" MATCHES ".*\\.h")
			message(STATUS "HEADER FILE ADDED ${from_path}/${elem}")
			list(APPEND header_files "${from_path}/${elem}")
    elseif("${elem}" MATCHES ".*\\.hpp")
			message(STATUS "HEADER FILE ADDED ${from_path}/${elem}")
			list(APPEND header_files "${from_path}/${elem}")
		else()
			message(STATUS "[INFO] SUB_DIRECTORY IS IGNORED ${from_path}/${elem}")
		endif()
	endif()
endforeach()
list(LENGTH source_files source_files_list_len)
message(STATUS "NUMBER OF SOURCE FILES GATHERED ${source_files_list_len}")
if(${source_files_list_len} GREATER 0)
  message(STATUS "PRIVATE TARGET SOURCES ${source_files_list_len} FOR ${target_proj}")
  print_list("${source_files}")
  target_sources(${target_proj} PRIVATE "${source_files}")
endif()
list(LENGTH header_files header_files_list_len)
message(STATUS "NUMBER OF HEADER FILES GATHERED ${header_files_list_len}")
if(${header_files_list_len} GREATER 0)
  message(STATUS "PUBLIC TARGET SOURCES  FOR ${target_proj}")
  print_list("${header_files}")
  target_sources(${target_proj} PRIVATE "${header_files}")
endif()
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${header_files} ${source_files} )
endfunction()

function(te_group_and_append SRCS from_path)
message(STATUS "group_and_append: SETTING TARGET SOURCES  FOR ${target_proj} STARTING IN ${from_path}")
set(source_files "")
set(header_files "")
file(GLOB subDirs RELATIVE ${from_path} ${from_path}/*)
# create list of files
foreach(elem ${subDirs})
	if(EXISTS ${from_path}/${elem})
		if("${elem}" MATCHES ".*\\.cpp")
			message(STATUS "SOURCE FILE ADDED ${from_path}/${elem}")
			list(APPEND SRCS "${from_path}/${elem}")
		elseif("${elem}" MATCHES ".*\\.h")
			message(STATUS "HEADER FILE ADDED ${from_path}/${elem}")
			list(APPEND SRCS "${from_path}/${elem}")
		else()
			message(STATUS "[INFO] SUB_DIRECTORY IS IGNORED ${from_path}/${elem}")
		endif()
	endif()
endforeach()
#list(LENGTH source_files source_files_list_len)
message(STATUS "SOURCE FILES GATHERED ${SRCS}")
endfunction()

# given file list will capture folder structure
function(te_source_group FILES)
  foreach(FILE ${FILES}) 
    #convert source file to absolute
	  get_filename_component(ABSOLUTE_PATH "${FILE}" ABSOLUTE)
	
    # Get the directory of the absolute source file
    get_filename_component(PARENT_DIR "${ABSOLUTE_PATH}" DIRECTORY)
    
    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
	
    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    set(GROUP "${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
  endforeach()
endfunction()

MACRO(TE_GROUP_SRC SRCS)
  foreach(FILE ${SRCS}) 
    #convert source file to absolute
	  get_filename_component(ABSOLUTE_PATH "${FILE}" ABSOLUTE)
	
    # Get the directory of the absolute source file
    get_filename_component(PARENT_DIR "${ABSOLUTE_PATH}" DIRECTORY)
	
    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
	
    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")
	
    # Group into "Source Files" and "Header Files"
    if ("${FILE}" MATCHES ".*\\.cpp")
      set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
      set(GROUP "Header Files${GROUP}")
    endif()
    source_group("${GROUP}" FILES "${FILE}")
  endforeach()
ENDMACRO(TE_GROUP_SRC)

