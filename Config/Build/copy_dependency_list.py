import sys
import os.path
import shutil

'''
    This script takes a file as an argument which contains list of copy commands.
    Copy commands are usually contains pair of destination and target source string that is
    concatenated by @ symbol. Each command is separated by ;. This is usually for copying 
    dependency dlls or files to build folder so executable can find them. If a given path or source
    is not valid script will skip them. In this case, program might not run as expected. Use it at your own risk.
'''
if __name__ == "__main__":
    filename = sys.argv[1]
    start_print_str = "\n"+"-"*32 + f"[Python Script: {sys.argv[0]} - Copying dependencies]" + "-"*32
    print(start_print_str)
    if os.path.isfile(filename):
        f = open(filename, "r")
        content = f.read()
        copy_commands = content.split(";")
        print(f"-- Number of copy tasks: {len(copy_commands)}")
        count = 0
        for cmd in copy_commands:
            # destination and copy target is separared by @ so we need to split
            copy_destination, copy_target = cmd.split("@") 

            # strip if any new line is exist
            copy_destination = copy_destination.strip("\n")
            copy_target = copy_target.strip("\n")
            if (os.path.exists(copy_target)):
                if not os.path.exists(copy_destination):
                    print(f"Directory {copy_destination} is not exitst, creating a new directory")
                    os.makedirs(copy_destination)
                shutil.copy(copy_target, copy_destination)
                print(f"-- Copying: {copy_target} to Destination: {copy_destination} ...")
                count += 1
            else:
                print(f"-- Invalid Source: {copy_target} or Destination: {copy_destination} skipping copy operation which may affect functionality")

        print(f"-- Copy operations completed: {count}")
        end_message = "Python Script End"
        diff = len(start_print_str) - len(end_message)
        dash_count = diff // 2
        print("-"*dash_count + "Python Script End" + "-"*dash_count+"\n")
        f.close()
    else:
        print(f"[ERROR] given argument is not a valid file arg:{filename}")
