#pragma once
#include <TorcGfx/HandleRegistry.h>

class EditorAssetBrowserPanel;
class EditorLogPanel;
class ShaderResourceRenderTarget;

class TorcEditor : public IEditor, public ISystemEventListener, public IWindowEventListener
{
public:
	TorcEditor(EditorCreateDesc desc);
	~TorcEditor();
	
	virtual void Initialize() override;
	virtual void GetDesc(EditorCreateDesc& desc) override {}
	virtual void OnFrameBegin() override;
	virtual void OnFrameEnd() override;
	virtual void OnSystemEvent(SystemEvent event, uint64 wparam, uint64 lparam) override;
	virtual bool OnWindowEvent(TORC_HWND hWnd, uint32 msg, uint64 wparam, uint64 lparam) override;
private:
	void EnableDockSpace();
	void CreateImGuiResources();
	void CreateLogOutputPanel();
	void CreatePlaceHolderPanel();
	void SetDarkThemeColors();

	EditorCreateDesc m_desc;
	RenderTargetHandle m_rtHandle;
	DepthStencilStateHandle m_dssHandle;

	//Panels
	EditorAssetBrowserPanel* m_assetBrowserPanel; 
	EditorLogPanel* m_editorLogPanel;

	bool m_sysQuit;
	std::string m_editorConfigPath;
	ShaderResourceRenderTarget* m_srvRT;
};