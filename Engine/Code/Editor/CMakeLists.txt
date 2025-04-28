set(EDITOR_BUILD_PROPS "EngineOutputDirectory:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" 
						"MSBuildProjectExtensionsPath:$(EngineOutputDirectory)\\$(Configuration)\\"
						"BaseIntermediateOutputPath:$(EngineOutputDirectory)\\$(Configuration)\\")

project(TorcEditor VERSION 0.1.0 LANGUAGES CSharp)

include(CSharpUtilities)
set(CMAKE_CSharp_FLAGS "/langversion:8 /platform:x64")
include_external_msproject(
    TorcEditor "${CMAKE_CURRENT_SOURCE_DIR}/TorcEditor.csproj")
	
	 set_target_properties(
     TorcEditor PROPERTIES
	 VS_GLOBAL_PROJECT_TYPES "{60dc8134-eba5-43b8-bcc9-bb4bc16c2548};{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}")

set_target_properties(TorcEditor PROPERTIES FOLDER "Engine/Code/Editor")

execute_process(COMMAND python Config/Build/create_editor_config_props.py ${CMAKE_CURRENT_LIST_DIR} ${EDITOR_BUILD_PROPS})