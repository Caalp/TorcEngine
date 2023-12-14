#include "pch.h"
#include "TorcEditor.h"

#include "Panels/EditorAssetBrowserPanel.h"
#include "Panels/EditorLogPanel.h"

#include <ImGui/imgui.h>
#include <ImGui/backend/imgui_impl_dx11.h>
#include <ImGui/backend/imgui_impl_win32.h>

#include <Core/Application.h>
#include <Core/TorcSystem/ISystem.h>
#include <Renderer/Renderer.h>
#include <Renderer/GPUObjects/RenderTarget.h>
#include <Renderer/GPUObjects/Texture.h>
#include <Renderer/GPUObjects/DepthStencilBuffer.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static uint32 windowWidth = 800, windowHeight = 600;

TorcEditor::TorcEditor(EditorCreateDesc desc)
	: m_desc(desc)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	io.WantSaveIniSettings = true;
	io.IniFilename = NULL;

	std::string engineRootDir = Torc::Platform::GetEngineRootDirectory();
	m_editorConfigPath = engineRootDir + "\\TorcEngine\\Tools\\TorcEditor\\editor.ini";

	ImGui::LoadIniSettingsFromDisk(m_editorConfigPath.c_str());
	SetDarkThemeColors();
}

TorcEditor::~TorcEditor()
{
	ImGui::SaveIniSettingsToDisk(m_editorConfigPath.c_str());
	ImGui::DestroyContext();
	
	if (m_editorLogPanel)
	{
		delete m_editorLogPanel;
	}
	if (m_assetBrowserPanel)
	{
		delete m_assetBrowserPanel;
	}

	Renderer* rr = gEnv->rr;
	rr->ReleaseInternalResourceByHandle(m_rtHandle);
	rr->ReleaseInternalResourceByHandle(m_dssHandle);
}

void TorcEditor::Initialize()
{
	m_editorLogPanel = new EditorLogPanel;
	m_assetBrowserPanel = new EditorAssetBrowserPanel;
	m_sysQuit = false;
}

void TorcEditor::OnFrameBegin()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	EnableDockSpace();

	// set imgui rt, sets depth enabled
	gEnv->rr->SetRenderTarget(m_rtHandle);
	
	gEnv->rr->ClearDepthStencil(m_srvRT->GetDepthStencilBuffer()->m_underlyingType, true, true, 1.0f, 0u);
	math::Vec4f color = { 1.0f, 0.0f, 0.0f, 1.0f };
	gEnv->rr->ClearRenderTarget(m_srvRT, color);
	gfx::ViewportDesc vpDesc;
	vpDesc.width = (float)windowWidth;
	vpDesc.height = (float)windowHeight;
	vpDesc.maxDepth = 1.0f;
	vpDesc.minDepth = 0.0f;
	vpDesc.topLeftX = 0.0f;
	vpDesc.topLeftY = 0.0f;
	gEnv->rr->SetViewport(vpDesc);

	static bool demoWnd = false;
	ImGui::ShowDemoWindow(&demoWnd);

	CreateLogOutputPanel();
	CreatePlaceHolderPanel();
	m_assetBrowserPanel->OnEditorDraw();
}

void TorcEditor::OnFrameEnd()
{
	if (m_sysQuit)
	{
		return;
	}

	// reset rt back to main one
	gEnv->rr->ResetRenderTarget(false);
	static bool isOpen = false;
	ImGui::Begin("Viewport", &isOpen, ImGuiWindowFlags_NoResize);
	ImGui::Image(m_srvRT->GetShaderResource()->m_underlyingType, ImVec2(800, 600));
	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
}

void TorcEditor::OnSystemEvent(SystemEvent event, uint64 wparam, uint64 lparam)
{
	switch (event)
	{
	case SystemEvent::SYSTEM_EVENT_RENDERER_INITIALIZED:
	{
		ID3D11Device* device = (ID3D11Device*)gEnv->rr->GetGFXBackend()->GetDevice();
		ID3D11DeviceContext* context = (ID3D11DeviceContext*)gEnv->rr->GetGFXBackend()->GetContext();
		ImGui_ImplDX11_Init(device, context);
		ImGui_ImplWin32_Init(gEnv->application->GetMainWindowHandle());
		CreateImGuiResources();
	}
	break;
	case SystemEvent::SYSTEM_EVENT_MAIN_WINDOW_INITIALIZED:
		gEnv->application->RegisterWindowEventListener(this, "TorcEditor");
		break;
	case SystemEvent::SYSTEM_EVENT_ENGINE_SHUTDOWN:
	{
		m_sysQuit = true;
	}
	break;
	case SystemEvent::SYSTEM_EVENT_WINDOW_SET_FOCUSE:
	{
		// rebuild directory tree
		m_assetBrowserPanel->ReinitializeDirectoryTree();
		LOG_INFO(LogChannel::LC_Core, "SystemEvent::SYSTEM_EVENT_WINDOW_SET_FOCUSE");
	}
	break;
	default:
		break;
	}
}

bool TorcEditor::OnWindowEvent(TORC_HWND hWnd, uint32 msg, uint64 wparam, uint64 lparam)
{
	return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wparam, lparam);
}

void TorcEditor::EnableDockSpace()
{
	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | 
						ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	float minWinSizeX = style.WindowMinSize.x;
	style.WindowMinSize.x = 370.0f;
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	style.WindowMinSize.x = minWinSizeX;
	ImGui::End();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New", "Ctrl+N"))
			{
				printf("New Clicked!\n");
				//ImGui::End();
				//return;
			}

			if (ImGui::MenuItem("Open...", "Ctrl+O"))
				return;

			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
				return;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Show Demo Window"))
			{
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void TorcEditor::CreateImGuiResources()
{
	gfx::RenderTargetDesc rtTextureDesc;
	rtTextureDesc.createMatchingDepthView = true;
	rtTextureDesc.format = gfx::TORC_GFX_RESOURCE_DATA_FORMAT::FORMAT_B8G8R8A8_UNORM;
	rtTextureDesc.viewDimension = gfx::TORC_GFX_RTV_DIMENSION::RTV_DIMENSION_TEXTURE2D;
	rtTextureDesc.textureDesc.usage = gfx::TORC_GFX_RESOURCE_USAGE::USAGE_GPU_READ_AND_WRITE;
	rtTextureDesc.textureDesc.arraySize = 1;
	rtTextureDesc.textureDesc.bindFlags = gfx::TORC_GFX_RESOURCE_BIND_FLAG::BIND_RENDER_TARGET | gfx::TORC_GFX_RESOURCE_BIND_FLAG::BIND_SHADER_RESOURCE;
	rtTextureDesc.textureDesc.cpuAccessFlags = gfx::TORC_GFX_CPU_ACCESS_FLAG::NO_ACCESS;
	rtTextureDesc.textureDesc.width = windowWidth;
	rtTextureDesc.textureDesc.height = windowHeight;
	rtTextureDesc.textureDesc.mipLevels = 0;
	rtTextureDesc.textureDesc.sampleDesc.count = 1;
	rtTextureDesc.textureDesc.sampleDesc.quality = 0;
	rtTextureDesc.textureDesc.format = rtTextureDesc.format;
	rtTextureDesc.textureDesc.miscFlags = 0;

	m_rtHandle = gEnv->rr->CreateRenderTarget(rtTextureDesc);
	IGPUResource* rtRes = gEnv->rr->GetResourceByHandle(m_rtHandle);
	m_srvRT = dynamic_cast<ShaderResourceRenderTarget*>(rtRes);
}

void TorcEditor::CreateLogOutputPanel()
{
	bool static p_open = false;
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
	ImGui::Begin("Console", &p_open);
	ImGui::End();
	m_editorLogPanel->Draw("Console", &p_open);
}

void TorcEditor::CreatePlaceHolderPanel()
{
	bool static p_open = false;
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
	static const ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse;
	ImGui::Begin("PlaceHolderPanel1", &p_open, windowFlags);
	ImGui::End();
}

void TorcEditor::SetDarkThemeColors()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;
	colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.105f, 0.11f, 1.0f);
	colors[ImGuiCol_Header] = ImVec4(0.2f, 0.205f, 0.21f, 1.0f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.3f, 0.305f, 0.31f, 1.0f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.15f, 0.1505f, 0.151f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.2f, 0.205f, 0.21f, 1.0f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.305f, 0.31f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.1505f, 0.151f, 1.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.205f, 0.21f, 1.0f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3f, 0.305f, 0.31f, 1.0f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.15f, 0.1505f, 0.151f, 1.0f);
	colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.1505f, 0.151f, 1.0f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.38f, 0.3805f, 0.381f, 1.0f);
	colors[ImGuiCol_TabActive] = ImVec4(0.28f, 0.2805f, 0.281f, 1.0f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.1505f, 0.151f, 1.0f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.2f, 0.205f, 0.21f, 1.0f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.1505f, 0.151f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.1505f, 0.151f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.95f, 0.1505f, 0.951f, 1.0f);
}