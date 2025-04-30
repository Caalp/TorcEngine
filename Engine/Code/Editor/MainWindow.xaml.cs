using System;
using System.Windows;
using TorcEditor.ProjectBrowser;
using System.Diagnostics;

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

            Editor editor = new Editor();
            if (!editor.Init())
            {
                MessageBox.Show("Editor Initialization is failed.");
                System.Windows.Application.Current.Shutdown();
            }
           
            ProjectBrowserView pbv = new ProjectBrowserView();
            pbv.Show();
            
        }
        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
            System.Windows.Application.Current.Shutdown();
        }

    }
}
