import sys
import os.path
import shutil

'''
    This script takes a string as an argument which will be defining properties. Using these properties a props file will be created.
    This file is used by MSBuild system by editor's vs project. It will contain common paths and configs that will be used
    by MSBuild and referred in .csproj file. Essentially, we will create Directory.Build.props file.
'''

settings_dict = {
    'EngineOutputDirectory' : '',
    'MSBuildProjectExtensionsPath' : '',
    'BaseIntermediateOutputPath' : ''
}

'''
 <EngineOutputDirectory>C:\\Users\\calp\\source\\repos\\TorcEngine\\build\\windows_vs2022</EngineOutputDirectory>
	        <MSBuildProjectExtensionsPath>$(EngineOutputDirectory)\\bin\$(Configuration)\\</MSBuildProjectExtensionsPath>
		    <BaseIntermediateOutputPath>$(EngineOutputDirectory)\\bin\$(Configuration)\\</BaseIntermediateOutputPath>
'''

xml_format = '''<?xml version="1.0" encoding="utf-8"?>
<Project>
    <PropertyGroup>
{0}
    </PropertyGroup>
</Project>  
'''

filename = 'Directory.Build.props'

def GetPropertyEntry(key, value):
    return f"<{key}>{value}</{key}>"

def ProcessAndAdd(arg):
    key,val = arg.split(":", 1) # key:val key should match one of the keys from settings_dict
    val = val.replace("/", "\\\\")
    outStr = "\t\t"
    if key in settings_dict:
        outStr += GetPropertyEntry(key, val)
        outStr += "\n"
        return outStr
    else:
        print(f"-- [ERROR] Given key: {key} is not valid, check settings_dict for matching key, skipping this entry...")
        return ""

if __name__ == "__main__":
    current_path = sys.argv[1]
    if not os.path.exists(current_path):
        sys.exit(f"Given path is not exists {current_path}. Aborting...")

    fullpath = current_path+"\\"+filename
    start_print_str = "\n"+"-"*32 + f"[Python Script: {sys.argv[0]} - TorcEditor Directory.Build.props file]" + "-"*32
    print(start_print_str)

    # create a fresh file 'w' will erase the content and recreate a file if one already exists
    f = open(fullpath, "w")
    values = ""
    for arg in sys.argv[2:]:
        if arg.find(";") != -1:
            args = arg.split(";")
            for arg_in in args:
                values += ProcessAndAdd(arg_in)
        else:
            values += ProcessAndAdd(arg)
    new_str = xml_format.format(values)
    f.write(new_str)

    print(f"\n + File {filename} created in the directory {current_path}\n")

    end_message = "Python Script End"
    diff = len(start_print_str) - len(end_message)
    dash_count = diff // 2
    print("-"*dash_count + "Python Script End" + "-"*dash_count+"\n")
    
    f.close()
