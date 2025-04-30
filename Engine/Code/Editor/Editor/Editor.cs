using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace TorcEditor
{
    internal class Editor
    {
        public static readonly string EditorProjectName = "TorcEditor.csproj";
        public static readonly string EngineJson = "engine.json";
        public static readonly string EditorCurrentDirectory = Environment.CurrentDirectory;
        public static readonly string EngineName = "TorcEngine";
        public static string EditorExecutablePathAbs = "";
        public static string EditorProjectDirectory = "";
        public static string EngineSourceDirectory = "";
        
        public bool Init()
        {
            bool init = true;
            init |= InitEditorConstants();
            return init;
        }

        
        private string SearchFileInDirectory(string directory, string fileToSearch)
        {
            DirectoryInfo info = new DirectoryInfo(directory);
            FileInfo[] files = info.GetFiles();

            foreach (FileInfo file in files)
            {
                if (file.Name == fileToSearch)
                {
                    return file.FullName;
                }
            }
            return string.Empty;
        }

        // searches directories starting from startDirectory to all subdirectories
        public string SearchFileInSubdirectories(string startDirectory, string fileToSearch)
        {
            if (!Directory.Exists(startDirectory))
            {
                Debug.WriteLine($"{startDirectory} is not a valid directory.");
                return "";
            }

            string file = SearchFileInDirectory(startDirectory, fileToSearch);
            if (file != string.Empty)
            {
                return file;
            }

            string[] directories = Directory.GetDirectories(startDirectory);
            foreach (string dir in directories)
            {
                string result = SearchFileInSubdirectories(dir, fileToSearch);
                if (result != string.Empty)
                {
                    return result;
                }
            }

            return string.Empty;
        }

        /// <summary>
        /// Search given file starting from given directory in the upwards direction
        /// just searches parent directories without going into their any subdirectories
        /// </summary>
        public string SearchFileInParentDirectoriesShallow(string startDirectory, string fileToSearch)
        {
            if (!Directory.Exists(startDirectory))
            {
                Debug.WriteLine($"{startDirectory} is not a valid directory.");
                return string.Empty;
            }

            string file = SearchFileInDirectory(startDirectory, fileToSearch);
            if (file != string.Empty)
            {
                return file;
            }

            string[] directories = Directory.GetDirectories(startDirectory);
            foreach (string dir in directories)
            {
                DirectoryInfo dire = new DirectoryInfo(dir);

                if (dire.FullName == startDirectory || !dire.Exists)
                {
                    continue;
                }
                
                string result = SearchFileInDirectory(dire.FullName, fileToSearch);
                if (result != string.Empty)
                {
                    return result;
                }
            }

            DirectoryInfo dirInfo = Directory.GetParent(startDirectory);
            var lookup = dirInfo.GetDirectories().ToLookup(x => x.Name, x => x.Name == EngineName);
            if (lookup[EngineName].Any<bool>() == true)
            {
                return string.Empty;
            }
            return SearchFileInParentDirectoriesShallow(dirInfo.FullName, fileToSearch);
        }

        private bool InitEditorConstants()
        {
            string engineSourcePath = SearchFileInParentDirectoriesShallow(EditorCurrentDirectory, EngineJson);
            EngineSourceDirectory = GetDirectory(engineSourcePath);

            string editorProjectAbsPath = SearchFileInSubdirectories(EngineSourceDirectory, EditorProjectName);
            EditorProjectDirectory = GetDirectory(editorProjectAbsPath);

            return EngineSourceDirectory != string.Empty && EditorProjectDirectory != string.Empty;
        }


        /// <summary>
        /// Given absolute path of a file, returns containing directory of the file.
        /// </summary>
        public string GetDirectory(string absFilePath)
        {
            if (!File.Exists(absFilePath))
            {
                Debug.WriteLine($"{absFilePath} is not a valid file.");
                return "";
            }
            return new FileInfo(absFilePath).Directory.ToString();
        }
    }
}
