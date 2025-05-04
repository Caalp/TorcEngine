
te_add_target(SHARED SOURCE_GROUP
	NAME
		TorcEngine.Bridge
	NAMESPACE
		TETools
	TARGET_PROPERTIES
		FOLDER Engine/Code/Tools/TorcEngine.Bridge
	BUILD_DEPENDENCIES
		TE::Core
)

# add copy jobs to list to be copied later
#<copy_destination>@<copy_target>
# set_property(GLOBAL APPEND PROPERTY COPY_TARGET_DEPENDENCY_LIST 
# ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/TorcEditor@${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/TorcEngine.Bridge.dll 
# ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/TorcEditor@${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/TorcEngine.Bridge.dll)

add_custom_command(TARGET TorcEngine.Bridge POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:TorcEngine.Bridge>/TorcEngine.Bridge.dll"
        "$<TARGET_FILE_DIR:TorcEngine.Bridge>/${EDITOR_PROJECT_NAME}/TorcEngine.Bridge.dll"
)