#pragma once

namespace Torc
{
	struct AppCreateParams
	{
		uint16_t wndPosX;
		uint16_t wndPosY;
		uint16_t wndWidth;
		uint16_t wndHeight;
		const char* wndCaption;
		const char* cmdLineArgs;
	};

	class Application
	{
	public:
		static Application* Instance();
		static bool Initialize(void* appConfig);
		static bool Run(void* appConfig);
		static void Shutdown();
	private:
		bool m_isRunning;
		bool m_isSuspended;
		float m_dt;
		AppCreateParams m_createParams;
	};
}

