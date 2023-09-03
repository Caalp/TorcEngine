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
using System.Windows.Navigation;
using System.Windows.Shapes;
using TorcEditor.ProjectBrowser;
using TorcEditor.WorldEditor;

namespace TorcEditor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            //Project.CreateProjectTemplatesXML();
            ProjectBrowserView pbv = new ProjectBrowserView();
            //DirectoryTree testTree = new DirectoryTree("./").Create();

            //foreach (DirectoryEntry item in testTree)
            //{
            //    System.Diagnostics.Debug.WriteLine(item.FullPath);
            //}
            pbv.Show();
            
        }
        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
            System.Windows.Application.Current.Shutdown();
        }

    }
}
