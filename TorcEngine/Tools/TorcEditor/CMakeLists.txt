project(TorcEditor VERSION 0.1.0 LANGUAGES CSharp)

include(CSharpUtilities)
set(CMAKE_CSharp_FLAGS "/langversion:8 /platform:x64")
include_external_msproject(
    TorcEditor "${CMAKE_CURRENT_SOURCE_DIR}/TorcEditor.csproj")
	
	 set_target_properties(
     TorcEditor PROPERTIES
	 VS_GLOBAL_PROJECT_TYPES "{60dc8134-eba5-43b8-bcc9-bb4bc16c2548};{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}")

set_target_properties(TorcEditor PROPERTIES FOLDER "Tools")

# file(GLOB_RECURSE cs_sources CONFIGURE_DEPENDS
	# ${CMAKE_CURRENT_SOURCE_DIR}/*.xaml
	# ${CMAKE_CURRENT_SOURCE_DIR}/*.xaml.cs
	# ${CMAKE_CURRENT_SOURCE_DIR}/*.cs
# )

# add_executable(TorcEditor ${cs_sources})
# set_target_properties(TorcEditor PROPERTIES FOLDER ${TOOLS_TARGET_FOLDER_NAME})
# set_target_properties(
    # TorcEditor PROPERTIES
    # VS_GLOBAL_PROJECT_TYPES "{60dc8134-eba5-43b8-bcc9-bb4bc16c2548};{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}"
# )

# csharp_set_designer_cs_properties(
	# Properties/AssemblyInfo.cs
    # # Properties/Resources.Designer.cs
    # # Properties/Resources.resx
    # Properties/Settings.Designer.cs
    # Properties/Settings.settings)



# file(GLOB_RECURSE cs_xaml_sources CONFIGURE_DEPENDS
	# ${CMAKE_CURRENT_SOURCE_DIR}/*.xaml
	# ${CMAKE_CURRENT_SOURCE_DIR}/*.xaml.cs
# )
# csharp_set_xaml_cs_properties(${cs_xaml_sources})

# set_property(SOURCE App.xaml PROPERTY VS_XAML_TYPE "ApplicationDefinition")
# set_property(TARGET TorcEditor PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.6.1")
# set_property(TARGET TorcEditor PROPERTY WIN32_EXECUTABLE TRUE)

# set_property(TARGET TorcEditor PROPERTY VS_DOTNET_REFERENCES
      # "Microsoft.CSharp"
      # "PresentationCore"
      # "PresentationFramework"
      # "System"
      # "System.Core"
      # "System.Data"
      # "System.Windows"
      # "System.Windows.Forms"
	  # "System.Runtime.Serialization"
	  # "System.Drawing"
	  # "System.Drawing.Image"
	  # "System.Collections"
      # "System.Data.DataSetExtensions"
      # "System.Net.Http"
      # "System.Xaml"
      # "System.Xml"
      # "System.Xml.Linq"
      # "WindowsBase")
	  
	  # install(TARGETS TorcEditor EXPORT sampleAppTargets
  # RUNTIME DESTINATION TorcEditor/
  # ARCHIVE DESTINATION TorcEditor/
  # LIBRARY DESTINATION TorcEditor/
# )
