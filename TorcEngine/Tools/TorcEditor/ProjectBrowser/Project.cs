using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;
using System.Runtime.Serialization;
using System.IO;
using System.Runtime.InteropServices;

namespace TorcEditor.ProjectBrowser
{

    [DataContract]
    public class ProjectTemplateInfo
    {
        [DataMember]
        public string ProjectType { get; set; }
        [DataMember]
        public byte[] Icon { get; set; }
        [DataMember]
        public byte[] Screenshot { get; set; } // to be displayed as snapshot for project type
    }
    [DataContract]
    public class ProjectData
    {
        [DataMember]
        public string Name { get; set; }
        [DataMember]
        public string ProjectType { get; set; }
        [DataMember]
        public string Path { get; set; }
        [DataMember]
        public DateTime CreationDate { get; set; }
        [DataMember]
        public DateTime LastUpdated { get; set; }
        [DataMember]
        public byte[] Icon { get; set; }
        [DataMember]
        public byte[] Screenshot { get; set; }
    }

    public class Project
    {
        [DllImport("../TorcEngine.Bridge.dll")]
        public static extern int TestAdd(int a);


        public enum ProjectType
        {
            Blank = 0,
            ThirdPerson,
            FirstPerson,
            Count
        }

        public Project()
        {

           string dir = System.IO.Directory.GetCurrentDirectory();
            int sum = TestAdd(10);
           projectTemplates = new ObservableCollection<ProjectTemplateInfo>();
           LoadProjectTemplates();           
        }

        public static string workingDir;
        public static string projectDir;

        private readonly ObservableCollection<ProjectTemplateInfo> projectTemplates;
        public static ObservableCollection<Tuple<string, ProjectData>> createdProjectDirs = new ObservableCollection<Tuple<string, ProjectData>>();
        public ObservableCollection<Tuple<string, ProjectData>> MyProjects { get { return createdProjectDirs;}}

        public ObservableCollection<ProjectTemplateInfo> ProjectTemplates => projectTemplates;

        // projects created by user previously 
        private static ObservableCollection<ProjectData> _projects = new ObservableCollection<ProjectData>();

        public ObservableCollection<ProjectData> Projects { get { return _projects; } }

    
        public bool LoadProjectTemplates()
        {
            // Get path for the templates
            string workingDir = Environment.CurrentDirectory;
            // TODO: Instead as a build step copy projectTemplates inside bin folder
            string projectDir = Directory.GetParent(workingDir).Parent.Parent.Parent.FullName+"\\Code\\Tools\\TorcEditor";
            string templateDir = $@"{projectDir}\ProjectTemplates";

            foreach (var template in Directory.GetDirectories(templateDir))
            {
                string file = $@"{template}\template.xml";
                if (File.Exists(file))
                {
                    ProjectTemplateInfo templateInfo = DeserializeXML<ProjectTemplateInfo>.Read(file);
                    projectTemplates.Add(templateInfo);
                }
                else
                {
                    System.Diagnostics.Debug.WriteLine("Template file in directory: " + template.ToString() + "not exist");
                }

            }

            if (projectTemplates.Count != (uint)ProjectType.Count)
            {
                return false;
            }

            return true;
        }

    }
}
