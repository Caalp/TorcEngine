using System;
using System.Collections;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TorcEditor.WorldEditor
{
    class DirectoryTreeViewModel : ViewModelBase
    {

        private DirectoryTree _directoryTree;
        private string _parentDirectory;
        private ObservableCollection<DirectoryEntry> _directoryEntries;

        public DirectoryTreeViewModel()
        {
            _parentDirectory = " N/A ";
            _directoryTree = new DirectoryTree("./").Create();
            _directoryEntries = new ObservableCollection<DirectoryEntry>();
            _directoryEntries.Add(_directoryTree.GetDirectoryEntry());
        }
        public string ParentDirectory
        {
            get => _parentDirectory;
            set => _parentDirectory = value;
        }

        public ObservableCollection<DirectoryEntry> ParentEntry
        {
            get => _directoryEntries;
        }

    }
}
