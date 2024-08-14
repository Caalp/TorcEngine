
te_add_target(SHARED SOURCE_GROUP
	NAME
		TorcEngine.Bridge
	NAMESPACE
		TETools
	FILES_CMAKE
		te_bridge_files.cmake
	TARGET_PROPERTIES
		FOLDER Engine/Tools/TorcEngine.Bridge
	BUILD_DEPENDENCIES
		TE::Core
)

# add copy jobs to list to be copied later
#<copy_destination>@<copy_target>
set_property(GLOBAL APPEND PROPERTY COPY_TARGET_DEPENDENCY_LIST 
${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/TorcEditor@${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/TorcEngine.Bridge.dll 
${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/TorcEditor@${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/TorcEngine.Bridge.dll)