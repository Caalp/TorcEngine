using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;

namespace TorcEditor.WorldEditor
{
    public class DirectoryEntry
    {
        public DirectoryEntry(string name, string fullpath, DirectoryEntryType type, List<DirectoryEntry> children)
        {
            Name = name;
            FullPath = fullpath;
            EntryType = type;
            Children = children;
        }
        public string Name { get; set; }
        public string FullPath { get; set; }
        public DirectoryEntryType EntryType { get; set; }
        public List<DirectoryEntry> Children { get; set; }

        public bool IsFolder { get => (EntryType == DirectoryEntryType.Folder) || (EntryType == DirectoryEntryType.Parent); }
    }
    //public class DirectoryEntryEnumerator : IEnumerator
    //{
    //    private DirectoryEntry _list;
    //    int index = -1;

    //    public DirectoryEntryEnumerator(DirectoryEntry list)
    //    {
    //        _list = list;
    //    }

    //    public object Current
    //    {
    //        get
    //        {
    //            try
    //            {
    //                return _list.Children[index];
    //            }
    //            catch
    //            {
    //                throw new InvalidOperationException();
    //            }
    //        }
    //    }

    //    public bool MoveNext()
    //    {
    //        index++;
    //        return (index < _list.Children.Count);
    //    }

    //    public void Reset()
    //    {
    //        index = -1;
    //    }
    //}
    public enum DirectoryEntryType
    {
        Parent,
        Folder,
        File
    }

    public class DirectoryTree
    {
        private DirectoryEntry _parentEntry;
        private string _path;
        public DirectoryTree(string parentDir)
        {
            _path = parentDir;
        }

        public DirectoryTree Create()
        {

            _parentEntry = new DirectoryEntry("", _path, DirectoryEntryType.Parent, new List<DirectoryEntry>());
            CaptureDirectoryTree(_parentEntry);
           
            return this;
        }
        //public DirectoryEntryEnumerator GetEnumerator()
        //{
        //    return new DirectoryEntryEnumerator(_parentEntry);
        //}

        public DirectoryEntry GetDirectoryEntry()
        {
            return _parentEntry;
        }

        private void CaptureDirectoryTree(DirectoryEntry entry)
        {
            DirectoryInfo mainDir = new DirectoryInfo(entry.FullPath);

            if (entry.EntryType == DirectoryEntryType.Parent)
            {
                entry.Name = mainDir.Name;
            }
            FileSystemInfo[] items = mainDir.GetFileSystemInfos();
            foreach (FileSystemInfo item in items)
            {
                if (item is DirectoryInfo info)
                {
                    DirectoryEntry temp = new DirectoryEntry(
                        info.Name,
                        info.FullName,
                        DirectoryEntryType.Folder,
                        (info.GetDirectories().Length > 0 || info.GetFiles().Length > 0) ? new List<DirectoryEntry>() : null
                    );
                    entry.Children.Add(temp);
                    CaptureDirectoryTree(temp);
                }
                else if (item is FileInfo fileInfo)
                {
                    entry.Children.Add(new DirectoryEntry(
                        fileInfo.Name,
                        fileInfo.FullName,
                        DirectoryEntryType.File,
                        null
                    ));
                }
                else
                {
                    throw new IOException("Unsupported Type: " + ((FileInfo)item).FullName);

                }
            }
        }
    }
}
