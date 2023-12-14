#pragma once

class EditorLogPanel final : public ILogListener
{
public:
	EditorLogPanel();
	~EditorLogPanel();
	virtual void OnLog(const char* msg, LogChannel channel, LogSeverity severity) override;
	void Draw(const char* title, bool* p_open = NULL);
private:
	std::vector<uint8> m_logs;
	std::vector<int> m_lineOffsets;
};