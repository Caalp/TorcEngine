#include "pch.h"
#include "EditorLogPanel.h"

#include <Core/TorcSystem/ISystem.h>
#include <ImGui/imgui.h>

EditorLogPanel::EditorLogPanel()
{
	gEnv->logger->RegisterListener(this);
	m_lineOffsets.push_back(0);
}

EditorLogPanel::~EditorLogPanel()
{
	if (gEnv && gEnv->logger)
	{
		gEnv->logger->RemoveListener(this);
	}
}

void EditorLogPanel::OnLog(const char* msg, LogChannel channel, LogSeverity severity)
{
	int32 strLen = (int32)strlen(msg);
	uint32 lineOffsets = 0;
	for (int32 i = 0; i < strLen; ++i)
	{
		m_logs.push_back((uint8)msg[i]);
		if (msg[i] == '\n')
		{
			m_lineOffsets.push_back((m_lineOffsets.back() + i + 1));
		}
	}
}

void EditorLogPanel::Draw(const char* title, bool* p_open)
{
	if (!ImGui::Begin(title, p_open))
	{
		ImGui::End();
		return;
	}
	bool clear = ImGui::Button("Clear");
	ImGui::Separator();

	if (ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar))
	{
		if (clear)
		{
			m_logs.clear();
			m_lineOffsets.clear();
			m_lineOffsets.push_back(0);
		}

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		const char* buf = (const char*)m_logs.data();
		const char* buf_end = (const char*)(m_logs.data() + m_logs.size());
		ImGuiListClipper clipper;
		clipper.Begin((int32)m_lineOffsets.size());
		while (clipper.Step())
		{
			for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
			{
				const char* line_start = buf + m_lineOffsets[line_no];
				const char* line_end = (line_no + 1 < m_lineOffsets.size()) ? (buf + m_lineOffsets[line_no + 1] - 1) : buf_end;
				ImGui::TextUnformatted(line_start, line_end);
			}
		}
		clipper.End();

		ImGui::PopStyleVar();
		if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		{
			ImGui::SetScrollHereY(1.0f);
		}
	}
	ImGui::EndChild();
	ImGui::End();
}
