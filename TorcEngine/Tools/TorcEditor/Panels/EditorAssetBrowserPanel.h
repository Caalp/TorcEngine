#pragma once

class EditorAssetBrowserPanel
{
	static constexpr char* assetDirectory = "TestGame\\Assets";
	struct MyTreeNode
	{
		static const int tree_node_flags;
		std::string name;
		std::string relativePath;
		bool isFolder;
		bool isSelected;
		bool isRoot;
		std::vector<MyTreeNode> nodes;

		static void DisplayNode(MyTreeNode* _nodes);
	};

public:
	EditorAssetBrowserPanel();
	void CreateHierarchyTree(std::string path, MyTreeNode* treeNodes);
	void OnEditorDraw();
	void ReinitializeDirectoryTree();
private:
	MyTreeNode* GetNodeByRelativePath(MyTreeNode* parentNode, const std::string& relativePath);
	bool m_isDirectoryTreeInitialized;
	std::string m_currentDirectory;
	MyTreeNode m_rootNode;
	static MyTreeNode* m_selectedNode;
};