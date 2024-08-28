import urllib.request
import git
import json
import sys
import os
import shutil
import tempfile

from git import RemoteProgress
import git.repo
from tqdm import tqdm
import stat
from subprocess import call
import zipfile
import requests
import io
import urllib

DownloadDirectory = ""
PackageDownloadDirectory = ""

class CloneProgress(RemoteProgress):
    def __init__(self, name):
        super().__init__()
        self.pbar = tqdm()
        self.pbar.set_description(f"Downloading {name}")

    def update(self, op_code, cur_count, max_count=None, message=''):
        self.pbar.total = max_count
        self.pbar.n = cur_count
        self.pbar.refresh()

class Items:
    def __init__(self, name, type, url, rev):
        self.name = name
        self.type = type
        self.url = url
        self.rev = rev
        self.isDownloaded = False
        self.requiresDownload = False
        self.useRevInName = False
    
    def GetName(self):
        return self.name
    
    def GetNameWithRev(self):
        return self.name + "_" + self.rev
    
    def GetType(self):
        return self.type

    def GetUrl(self):
        return self.url
    
    def GetRev(self):
        return self.rev
    
    def SetAsDownloaded(self):
        self.isDownloaded = True

    def GetUseRevInName(self):
        return self.useRevInName
    
    def IsSuccessfull(self):
        return self.isDownloaded == True
    
    def SetUseRevInName(self, useRev):
        self.useRevInName = useRev

    def SetRequiresDownload(self, download):
        self.requiresDownload = download
    
    def __eq__(self, str1):
        return (self.name == str1) or (self.name+'.zip' == str1)
    
def GetMD5(zipFile):
    from hashlib import md5
    hasher = md5()
    with open(zipFile, 'rb') as f:
        data = f.read()
        hasher.update(data)
        return hasher.hexdigest()

def on_rm_error(func, path, exc_info):
    #from: https://stackoverflow.com/questions/4829043/how-to-remove-read-only-attrib-directory-with-python-in-windows
    os.chmod(path, stat.S_IWRITE)
    os.unlink(path)  

def DeleteIteratively(path):
    if not os.path.exists(path):
        return
    if os.path.isfile(path):
        os.remove(path)
    if os.path.isdir(path):
        for e in os.listdir(path):
            if e.endswith('git'):
                tmp = os.path.join(path, e)
                # We want to unhide the .git folder before unlinking it.
                while True:
                    call(['attrib', '-H', tmp])
                    break
                shutil.rmtree(tmp, onerror=on_rm_error)
                continue
            f = os.path.join(path, e)
            DeleteIteratively(f)
        if len(os.listdir(path)) == 0:
            shutil.rmtree(path, onerror=on_rm_error)

def DownloadRequirements(downloadPath, reqs):
    tempDir = tempfile.mkdtemp()
    for req in reqs:
        if req.GetType() == "https":

            # TODO(cagri): check if zip already exists and compare against md5 here as well 
            filename = req.GetName() + ".zip"
            filepath = os.path.join(downloadPath, filename)
            print("https request for {} downloading...".format(filename))
            urllib.request.urlretrieve(req.GetUrl(), filepath)
            req.SetAsDownloaded()
        else:
            name = req.GetName()
            path = os.path.join(downloadPath, req.GetName())
            zipFile = path + ".zip"

            # zip file name with rev {name}_{rev}.zip
            zipFileWithRev = os.path.join(downloadPath, req.GetNameWithRev() + ".zip")
            if os.path.exists(zipFile):
                print(f"{name} package is found in {downloadPath} checking for validity... ->", end=" ", flush=True)
                # check sha sum
                rev = GetMD5(zipFile)
                if rev == req.GetRev():
                    print("{} rev is matching expected_rev: {}, curr_rev: {}".format(zipFile,  req.GetRev(), rev))
                    req.SetAsDownloaded()
                    continue
                else:
                    req.SetUseRevInName(True)
                    if os.path.exists(zipFileWithRev):
                        rev = GetMD5(zipFileWithRev)
                        if rev == req.GetRev():
                            print("{} rev is matching for expected_rev: {}, curr_rev: {}".format(zipFileWithRev, req.GetRev(), rev))
                            req.SetAsDownloaded()
                            continue
                    print(f"{zipFileWithRev} rev is not matching will redownload...")           

            tempPath = os.path.join(tempDir, name)
            print("Temp Download Path: {}".format(tempPath))  
            git.Repo.clone_from(req.url, tempPath, progress=CloneProgress(name))

            newZipFile = path + "_" + req.GetRev() + ".zip" if req.GetUseRevInName() else path + ".zip"
            with open(newZipFile, "wb") as archiveFile:
                git.Repo(tempPath).archive(archiveFile, format='zip')
            rev = GetMD5(newZipFile)
            if rev != req.GetRev():
                print("Downloaded package version is different than requirement. Current Rev: {}, Expected Rev: {}, Deleting {}, and continuing...". format(rev, req.GetRev(), newZipFile))
                os.remove(newZipFile)  
                continue
            req.SetAsDownloaded()
    
    #DeleteIteratively(tempDir)
    shutil.rmtree(tempDir, ignore_errors=True)
    

def DownloadRequirementsAsZip(downloadPath, reqs):
    import requests
    for item in reqs:
        response = requests.get(item.GetUrl(), stream=True)
        with open(os.path.join(downloadPath, item.GetName() + ".zip"), "wb") as handle:
            for data in tqdm(response.iter_content()):
                handle.write(data)

if __name__ == "__main__":

    '''
            TODO: 
            1. .git directory in the temp file is not removed due to windows not letting 
            2. If folder is exist verify md5 and use it instead else download. Which means even if we don't have the zip file but have the unzipped file we can 
            check md5 hash of the folder and see if it is maching the revision. If so, we can just skip downloading the package since it is already exists
    '''
    args = {}
    for i , arg in enumerate(sys.argv[1:]):
        x = arg.split('=', 1)
        key = None
        val = None
        if len(x) > 1:
            idx = x[0].rfind('-')
            key = x[0][idx+1:]
            val = x[1]
        else:
            key = i
            idx = x[0].rfind('-')
            val = x[0][idx+1 :]

        args[key] = val

    filepath = os.path.abspath(args["path"])
    if not os.path.isfile(filepath):
        print(f"file is not exist {filepath}")
        exit(-1)

    f = open(filepath)
    data = json.load(f)

    requireds = []
    # paths are relative to where bat file is called
    DownloadDirectory = data["DownloadPath"]
    skipDownload = data["SkipDownload"]
    DownloadDirectory = os.path.abspath(DownloadDirectory)
    PackageDownloadDirectory = os.path.join(DownloadDirectory, "downloaded_packages")
    print("Download Directory = {}".format(DownloadDirectory))
    if not os.path.exists(DownloadDirectory):
        print(f"Download directory is not exist creating directory {DownloadDirectory}")
        os.mkdir(DownloadDirectory)
        os.mkdir(PackageDownloadDirectory)
    if not os.path.exists(PackageDownloadDirectory):
        os.mkdir(PackageDownloadDirectory)
    
    for item in data["Dependencies"]:
        name = item["Name"]
        type = item["Source"]["Type"]
        url = item["Source"]["Url"]
        revision = item["Source"]["Revision"]

        requireds.append(Items(name, type, url, revision))
    
    if (skipDownload != True):
        DownloadRequirements(PackageDownloadDirectory, requireds)
    else:
        for req in requireds:
            req.SetAsDownloaded()

    #DownloadRequirementsAsZip(PackageDownloadDirectory, requireds)
    #report unsuccessfull downloads
    count = 0
    for req in requireds:
        if not req.IsSuccessfull():
            print(f"[ERROR] Downloading {req.GetName()} is failed")
            count += 1
    if count == 0:
        print("All requirements are downloaded successfully...")

    packageUnzipDirectory = os.path.join(DownloadDirectory, "packages")
    if not os.path.exists(packageUnzipDirectory):
        os.mkdir(packageUnzipDirectory)
    
    # we can unzip downloaded ones
    for e in os.listdir(PackageDownloadDirectory):
        fullpath = os.path.join(PackageDownloadDirectory, e)
        if not fullpath.endswith('.zip') or e not in requireds:
            continue
        
        unzipPath = packageUnzipDirectory
        with zipfile.ZipFile(fullpath, 'r') as zipRef:
            print(f"unzipping {e} to {packageUnzipDirectory}")
            #unzipPath = os.path.join(packageUnzipDirectory, e)
            # zip file has the name <name>.zip we remove .zip extension from folder name if . is found
            #dot = unzipPath.rfind('.')
            #if unzipPath.rfind('.') != -1:
            #    unzipPath = unzipPath[:dot]
            zipRef.extractall(unzipPath)
