import hashlib
import os
import sys

def GenerateMD5(filepath):
    if not os.path.exists(filepath):
        print("given path: {} is not exists.".format(filepath))
        exit(-1)

    if not filepath.endswith(".zip"):
        print("Only .zip file format is currently supported.")
        exit(-1)

    md5 = hashlib.md5()
    with open(filepath, "rb") as file:
        data = file.read()
        md5.update(data)
        return md5.hexdigest()

if __name__ == "__main__":

    arg1 = sys.argv[1]
    arg1 = arg1.split('=', 1)[1]

    print(f"md5:{GenerateMD5(arg1)}")