using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TorcEditor.ProjectBrowser;
using System.IO;
namespace TorcEditor
{
    public class ProjectTemplateUtils
    {
        public static bool CreateProjectTemplatesXML()
        {
            // Get path for the templates
            string workingDir = Environment.CurrentDirectory;
            string projectDir = Directory.GetParent(workingDir).Parent.Parent.FullName;
            string templateDir = $@"{projectDir}\ProjectTemplates";

            foreach (var template in Directory.GetDirectories(templateDir))
            {
                string file = $@"{template}\template.xml";
                ProjectTemplateInfo info = new ProjectTemplateInfo();
                info.ProjectType = Project.ProjectType.Blank.ToString();
                string imagePath = $@"{template}\icon.png";
                string screenshotPath = $@"{template}\screenshot.png";
                using (var ms = new MemoryStream())
                {
                    System.Drawing.Image.FromFile(imagePath).Save(ms, System.Drawing.Imaging.ImageFormat.Png);
                    info.Icon = ms.ToArray();
                }
                using (var ms = new MemoryStream())
                {
                    System.Drawing.Image.FromFile(screenshotPath).Save(ms, System.Drawing.Imaging.ImageFormat.Png);
                    info.Screenshot = ms.ToArray();
                }
                SerializeToXML<ProjectTemplateInfo>.Write(info, file);

            }

            //if (projectTemplates.Count != (uint)ProjectType.Count)
            //{
            //    return false;
            //}

            return true;
        }


    }
}
