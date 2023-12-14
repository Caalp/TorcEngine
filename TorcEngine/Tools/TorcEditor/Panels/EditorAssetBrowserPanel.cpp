#include "pch.h"
#include "EditorAssetBrowserPanel.h"

#include <ImGui/imgui.h>

EditorAssetBrowserPanel::MyTreeNode* EditorAssetBrowserPanel::m_selectedNode = nullptr;
const int EditorAssetBrowserPanel::MyTreeNode::tree_node_flags = ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_OpenOnArrow;

void EditorAssetBrowserPanel::MyTreeNode::DisplayNode(MyTreeNode* _nodes)
{
	auto& nodes = _nodes->nodes;
	auto processTreeNodes = [&nodes]()
	{
		for (int i = 0; i < nodes.size(); ++i)
		{
			// TODO(cagri): this logic causes duplication of the code, think a better way!
			ImGuiTreeNodeFlags nodeFlags = tree_node_flags;
			if (m_selectedNode == &nodes[i])
			{
				nodeFlags |= ImGuiTreeNodeFlags_Selected;
			}

			if (nodes[i].isFolder)
			{
				bool isOpen = ImGui::TreeNodeEx(nodes[i].name.c_str(), nodeFlags);
				if (ImGui::IsItemClicked())
				{
					nodes[i].isSelected = true;
					m_selectedNode = &nodes[i];
				}
				else
				{
					nodes[i].isSelected = false;
				}

				if (isOpen)
				{
					DisplayNode(&nodes[i]);
					ImGui::TreePop();
				}
			}
			else
			{
				ImGui::TreeNodeEx(nodes[i].name.c_str(), nodeFlags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);
			}
		}
	};

	static bool isRootOpen = false;
	if (_nodes->isRoot)
	{
		ImGuiTreeNodeFlags nodeFlags = tree_node_flags;
		if (m_selectedNode == _nodes)
		{
			nodeFlags |= ImGuiTreeNodeFlags_Selected;
		}
		isRootOpen = ImGui::TreeNodeEx(_nodes->name.c_str(), nodeFlags | ImGuiTreeNodeFlags_DefaultOpen);
		if (ImGui::IsItemClicked())
		{
			_nodes->isSelected = true;
			m_selectedNode = _nodes;
		}
		else
		{
			_nodes->isSelected = false;
		}
	}

	if (isRootOpen && _nodes->isRoot)
	{
		processTreeNodes();
		ImGui::TreePop();
	}
	else if (isRootOpen && !_nodes->isRoot)
	{
		processTreeNodes();
	}
}

EditorAssetBrowserPanel::EditorAssetBrowserPanel()
	: m_currentDirectory(assetDirectory)
	, m_isDirectoryTreeInitialized(false)
{
	m_rootNode.name = assetDirectory;
	m_rootNode.isFolder = true;
	m_rootNode.isRoot = true;
	m_rootNode.relativePath = m_currentDirectory;
	m_selectedNode = &m_rootNode;
}

void EditorAssetBrowserPanel::CreateHierarchyTree(std::string path, MyTreeNode* treeNodes)
{
	std::string ss = fs::GetWorkingDirectory();
	fs::SetWorkingDirectory(Torc::Platform::GetEngineRootDirectory());
	ss = fs::GetWorkingDirectory();
	std::string fullPath = fs::GetAbsolutePath(path.c_str()) + "\\*";
	_WIN32_FIND_DATAA data{};
	TORC_HANDLE handle = FindFirstFileA(fullPath.c_str(), &data);
	do
	{
		if (!strcmp(data.cFileName, ".") || !strcmp(data.cFileName, ".."))
		{
			continue;
		}
		MyTreeNode newNode{};
		newNode.name = data.cFileName;

		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			newNode.relativePath = path + "\\" + newNode.name;
			newNode.isFolder = true;
			CreateHierarchyTree(path + "\\" + std::string(data.cFileName), &newNode);
		}
		else
		{
			newNode.relativePath = path;
		}

		treeNodes->nodes.push_back(newNode);
	} while (FindNextFileA(handle, &data) != 0);
	FindClose(handle);
}

void EditorAssetBrowserPanel::OnEditorDraw()
{
	if (!m_isDirectoryTreeInitialized)
	{
		m_rootNode.nodes.clear();
		CreateHierarchyTree(assetDirectory, &m_rootNode);
		m_isDirectoryTreeInitialized = true;
	}

	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
	static const float cellPadding = 5.0f;
	static float cellSize = 64.0f;
	static float windowWidth = ImGui::GetWindowSize().x;
	static int columnCount = (int)(windowWidth / (cellSize + cellPadding));

	bool static p_open = false;
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse;
	ImGui::Begin("Asset Browser", &p_open, windowFlags);

	if (fs::GetWorkingDirectory() != Torc::Platform::GetEngineRootDirectory())
	{
		fs::SetWorkingDirectory(Torc::Platform::GetEngineRootDirectory());
	}
	
	windowWidth = ImGui::GetWindowSize().x;
	columnCount = (int)(windowWidth / (cellSize + cellPadding));
	
	std::string fullPath = fs::GetAbsolutePath(m_currentDirectory.c_str()) + "\\*";

	// TODO(cagri): Replace platform specific functions
	_WIN32_FIND_DATAA data{};
	TORC_HANDLE handle = FindFirstFileA(fullPath.c_str(), &data);
	float textHeight = ImGui::CalcTextSize(fullPath.c_str()).y + 10;
	if (ImGui::BeginTable("asset_browser", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY | ImGuiTableFlags_NoHostExtendX | ImGuiTableFlags_NoHostExtendY, ImVec2{ 0.0f , -textHeight }))
	{
		/*if (strcmp(m_currentDirectory.c_str(), assetDirectory) && data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (ImGui::Button("<-", ImVec2{ 16, 16 }))
			{
				m_currentDirectory = fs::GetParentDirectory(m_currentDirectory.c_str());
			}
			ImGui::Separator();
		}*/

		ImGui::TableSetupColumn("AssetBrowser_Col0", ImGuiTableColumnFlags_NoHeaderLabel | ImGuiTableColumnFlags_WidthFixed, 150.0f);
		ImGui::TableNextColumn();

		// draw tree
		MyTreeNode::DisplayNode(&m_rootNode);

		if (m_selectedNode && m_selectedNode->isSelected && m_currentDirectory != m_selectedNode->relativePath)
		{
			// re-eval selected node
			m_selectedNode = GetNodeByRelativePath(&m_rootNode, m_selectedNode->relativePath);
			if (m_selectedNode)
			{
				m_currentDirectory = m_selectedNode->relativePath;
			}
		}

		// draw files
		// TODO(cagri): Replace platform specific functions
		ImGui::TableNextColumn();
		static constexpr ImGuiTableFlags assetBrowserFlags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_NoHostExtendY | ImGuiTableFlags_NoHostExtendX | ImGuiTableFlags_SizingFixedSame;
		if (ImGui::BeginTable("AssetBrowser_Col1", columnCount, assetBrowserFlags, ImVec2{ 0.0f ,0.0f }))
		{
			// Get width and calculate the column count
			windowWidth = ImGui::GetWindowSize().x;
			columnCount = (int)(windowWidth / (cellSize + cellPadding));
			int currentItemIndex = 0;
			ImGui::TableNextRow();
			do
			{
				ImGui::TableSetColumnIndex(currentItemIndex % columnCount);
				if (!strcmp(data.cFileName, ".") || !strcmp(data.cFileName, ".."))
				{
					continue;
				}
				ImGui::Button(data.cFileName, ImVec2{ cellSize, cellSize });
				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						m_currentDirectory = m_currentDirectory + "\\" + std::string(data.cFileName);
					}
				}
				ImGui::TextWrapped(data.cFileName);
				currentItemIndex++;
				if (currentItemIndex % columnCount == 0 && currentItemIndex / columnCount >= 1)
				{
					ImGui::TableNextRow();
				}

			} while (FindNextFileA(handle, &data) != 0);
			ImGui::EndTable();

			FindClose(handle);
		}
		ImGui::EndTable();
	}

	ImGui::Separator();
	ImGui::TextColored(ImVec4{ 1.0f, 1.0f, 0.0f, 0.7f }, fullPath.c_str());
	ImGui::End();
}

void EditorAssetBrowserPanel::ReinitializeDirectoryTree()
{
	m_isDirectoryTreeInitialized = false;
}

EditorAssetBrowserPanel::MyTreeNode* EditorAssetBrowserPanel::GetNodeByRelativePath(MyTreeNode* parentNode, const std::string& relativePath)
{
	if (!parentNode)
	{
		return nullptr;
	}

	if (parentNode && parentNode->relativePath == relativePath)
	{
		return parentNode;
	}

	for (int32 nodeIndex = 0; nodeIndex < parentNode->nodes.size(); nodeIndex++)
	{
		MyTreeNode* node =  GetNodeByRelativePath(&parentNode->nodes[nodeIndex], relativePath);
		if (node)
		{
			return node;
		}
	}

	return nullptr;
}
