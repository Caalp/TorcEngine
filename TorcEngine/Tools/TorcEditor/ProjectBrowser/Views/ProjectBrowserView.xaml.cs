using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Collections.ObjectModel;
using System.Runtime.Serialization;
using System.IO;
using Microsoft.Win32;
using System.Windows.Forms;
using System.Security.AccessControl;
namespace TorcEditor.ProjectBrowser
{
    /// <summary>
    /// Interaction logic for ProjectBrowserView.xaml
    /// </summary>
    /// 
  
    public partial class ProjectBrowserView : Window
    {
        private string projectPath;
        private string defaultProjectPath;
        private string projectName;
        private string hiddenEngineFolder;
        
        public string ProjectPath
        { 
            get => projectPath; 
            set => projectPath = value;
        }

        public ProjectBrowserView()
        {
            defaultProjectPath = $@"{Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments)}\Torc Engine\";
            // I should move this out of here irrelevant
            hiddenEngineFolder = defaultProjectPath + ".torc";
            if (!Directory.Exists(hiddenEngineFolder))
            {
                DirectoryInfo dir = Directory.CreateDirectory(hiddenEngineFolder);
                dir.Attributes = FileAttributes.Directory | FileAttributes.Hidden;
            }

            if (!Directory.Exists(defaultProjectPath))
            {
                Directory.CreateDirectory(defaultProjectPath);
            }
            InitializeComponent();
            textBoxProjectPath.Text = defaultProjectPath;
            ReadCreatedProjectDirectories();
        }

        private void btnOpenFiles_Click(object sender, RoutedEventArgs e)
        {
            FolderBrowserDialog openFolderBrowserDialog = new FolderBrowserDialog();
            openFolderBrowserDialog.SelectedPath = $@"{Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments)}\Torc Engine\";
            DialogResult dr = openFolderBrowserDialog.ShowDialog();
            if (dr == System.Windows.Forms.DialogResult.OK)
            {
                projectPath = openFolderBrowserDialog.SelectedPath;
                textBoxProjectPath.Text = projectPath;
            }
        }

        private void buttonCreateProject_Click(object sender, RoutedEventArgs e)
        {
            labelInfo.Content = string.Empty;
            // Get both projectPath and projectName
            if (projectPath != null && projectName != null)
            {
                try
                {
                    string fullpath = System.IO.Path.Combine(projectPath, projectName);
                    if (!Directory.Exists(fullpath) && System.IO.Path.IsPathRooted(fullpath))
                    {
                        try
                        {
                            ProjectData projectData = new ProjectData();
                            Directory.CreateDirectory(fullpath);
                            
                            // put project def files in it
                            ProjectTemplateInfo templateInfo = listboxProjectTemplates.SelectedItem as ProjectTemplateInfo;
                            projectData.Icon = templateInfo.Icon;
                            projectData.Screenshot = templateInfo.Screenshot;
                            projectData.ProjectType = templateInfo.ProjectType;
                            projectData.Name = textBoxProjectName.Text;
                            projectData.CreationDate = DateTime.Now;
                            projectData.LastUpdated = DateTime.Now;
                            projectData.Path = fullpath;

                            SerializeToXML<ProjectData>.Write(projectData, $@"{fullpath}\proj");

                            // and register created project so we can check later
                            if (Directory.Exists(hiddenEngineFolder))
                            {
                                string projRegFile = $@"{hiddenEngineFolder}\torc_reg";
                                using (FileStream fs = File.Open(projRegFile, FileMode.Append))
                                {
                                    //fs.Write(Encoding.ASCII.GetBytes(fullpath+"\r\n"));
                                    fs.Close();
                                }
                            }

                        }
                        catch(Exception ex)
                        {
                            System.Windows.MessageBox.Show(ex.Message);
                        }
                    }
                    else
                    {
                        labelInfo.Content = "Project with given name is already exist in selected directory.";
                    }

                }
                catch(Exception ex)
                {
                    System.Diagnostics.Debug.WriteLine(ex.Message);
                }

                if (Directory.Exists(System.IO.Path.Combine(projectPath, projectName)))
                {
                    Window.GetWindow(this).Hide();
                    // open main editor window
                    App.Current.MainWindow.Show();
                }
            }

        }

        private void textBoxTextChangedEventHandler(object sender, TextChangedEventArgs e)
        {
            labelInfo.Content = String.Empty;
            DependencyObject obj = sender as DependencyObject;
            string name = obj.GetValue(FrameworkElement.NameProperty) as string;

            if (name == "textBoxProjectPath")
            {
                projectPath = textBoxProjectPath.Text;
            }
            else if(name == "textBoxProjectName")
            {
                projectName = textBoxProjectName.Text;
            }

            if ((projectName != String.Empty && projectPath != String.Empty) && (projectName != null && projectPath != null))
            {
                buttonCreateProject.IsEnabled = true;
                string fullpath = System.IO.Path.Combine(projectPath, projectName);
                if (Directory.Exists(fullpath) && System.IO.Path.IsPathRooted(fullpath))
                {
                    buttonCreateProject.IsEnabled = false;
                    // put a message saying project is already exist
                    labelInfo.Content = "Project with given name is already exist in selected directory.";
                }
            }
            else 
            {
                buttonCreateProject.IsEnabled = false;
            }



        }

        private void ReadCreatedProjectDirectories()
        {
            if (Directory.Exists(hiddenEngineFolder))
            {
                string projRegFile = $@"{hiddenEngineFolder}\torc_reg";
                try
                {
                    using var fs = new FileStream(projRegFile, FileMode.Open, FileAccess.Read);
                    using var sr = new StreamReader(fs, Encoding.ASCII);
                    string line = String.Empty;
                    while((line = sr.ReadLine()) != null)
                    {
                        if (Directory.Exists(line))
                        {
                            ProjectData data = new ProjectData();
                            data = DeserializeXML<ProjectData>.Read($@"{line}\proj");
                            Project.createdProjectDirs.Add(new Tuple<string, ProjectData>(line, data));
                        }
                    }
                }
                catch(Exception ex)
                {
                    System.Diagnostics.Debug.WriteLine(ex.Message);
                }

            }
        }

        private void buttonSelectProject_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.MessageBox.Show("Hello");
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
            System.Windows.Application.Current.Shutdown();
        }

        private void buttonOpenProject_Click(object sender, RoutedEventArgs e)
        {
            if (listboxMyProjects.SelectedIndex != -1)
            {
                Tuple<string, ProjectData> selectedItem = (Tuple<string, ProjectData>)listboxMyProjects.SelectedItem;
                if (Directory.Exists(selectedItem.Item2.Path))
                {
                    // load project related data

                    // show main window
                    Window.GetWindow(this).Hide();
                    App.Current.MainWindow.Show();
                }
                else
                {
                    // project is not exists or corrupted
                }
                    
            }
        }

        private void buttonCancel_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
