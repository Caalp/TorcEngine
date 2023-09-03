using System;
using System.Collections.Generic;
using System.Text;

namespace TorcEditor.ProjectBrowser
{
    public class ProjectInstance
    {
        public static Project Instance { get; } = new Project();
        public ProjectInstance() { }
    }
}

