#pragma once
#include "Core/TorcStd/Containers/Queue.h"
#include "Core/Platform/Platform.h"

#include <assert.h>
#include <map>
#include <string>
#include <deque>

inline std::string SystemTimeToString(const SystemTime& time)
{
	std::string strTime = std::to_string(time.day) + "." + std::to_string(time.month) + "." + std::to_string(time.year) + " " + std::to_string(time.hour) + "." + std::to_string(time.minute) + "." + std::to_string(time.second) + "." + std::to_string(time.milliseconds);
	return strTime;
}

enum SystemEvent
{
	SYSTEM_EVENT_WINDOW_MOVED,
	SYSTEM_EVENT_WINDOW_RESIZED,
	SYSTEM_EVENT_WINDOW_CLOSED,
	SYSTEM_EVENT_MAIN_WINDOW_INITIALIZED,
	SYSTEM_EVENT_MAIN_WINDOW_CLOSED,
	SYSTEM_EVENT_WINDOW_SET_FOCUSE,

	SYSTEM_EVENT_ENGINE_SHUTDOWN,

	SYSTEM_EVENT_GAME_PAUSED,
	SYSTEM_EVENT_GAME_RESUMED,
	SYSTEM_EVENT_RENDERER_INITIALIZED,
	SYSTEM_EVENT_SYSTEM_INIT_BEGAN,
	SYSTEM_EVENT_SYSTEM_INIT_DONE,
	SYSTEM_EVENT_DEVICE_CHANGED,

	SYSTEM_EVENT_USER
};

struct InputEvent;
class BaseInput;
class Renderer;
class PluginLoader;
class Application;
class System;
class BaseInput;
class PlatformInput;
class ILogger;

namespace gfx
{
	class ITorcGfxBackend;
}


struct EditorCreateDesc
{
	uint32 width;
	uint32 height;
	const char* windowTitle;
};

struct ISystemEventListener
{
	virtual ~ISystemEventListener() {}
	virtual void OnSystemEvent(SystemEvent event, uint64 wparam, uint64 lparam) = 0;
};

struct IWindowEventListener
{
	virtual ~IWindowEventListener() {}
	virtual bool OnWindowEvent(TORC_HWND hWnd, uint32 msg, uint64 wparam, uint64 lparam) = 0;
};

struct IWindowEventDispatcher
{
	virtual ~IWindowEventDispatcher() {}
	virtual bool RegisterListener(IWindowEventListener* pListener, const char* szName) = 0;
	virtual bool RemoveListener(IWindowEventListener* pListener) = 0;

	virtual void OnWindowEvent(TORC_HWND hWnd, uint32 msg, uint64 wparam, uint64 lparam, bool force_queue = false) = 0;
	virtual void Update() = 0;
};

//! Structure used for getting notified when a system event occurs.
struct ISystemEventDispatcher
{
	virtual ~ISystemEventDispatcher() {}
	virtual bool RegisterListener(ISystemEventListener* pListener, const char* szName) = 0;
	virtual bool RemoveListener(ISystemEventListener* pListener) = 0;

	virtual void OnSystemEvent(SystemEvent event, UINT_PTR wparam, UINT_PTR lparam, bool force_queue = false) = 0;
	virtual void Update() = 0;
};

struct IInputEventListener
{
	virtual ~IInputEventListener() {}
	virtual bool OnInputEvent(InputEvent inputEvent) = 0;
};

struct IInputEventDispatcher
{
	virtual ~IInputEventDispatcher() {}
	virtual bool RegisterListener(IInputEventListener* pListener, const char* szName) = 0;
	virtual bool RemoveListener(IInputEventListener* pListener) = 0;

	virtual void OnInputEvent(InputEvent event) = 0;
	virtual void Update() = 0;
};

struct SystemGlobalEnvironment
{
	ILogger* logger;
	BaseInput* baseInput;
	PlatformInput* platformInput;
	Application* application;
	Renderer* rr;
	PluginLoader* pluginLoader;
	struct IEditor* editor;
	gfx::ITorcGfxBackend* gfx;

	uint64 mainThreadId;
};

struct IEditor
{
	virtual void Initialize() = 0;
	virtual void GetDesc(EditorCreateDesc& desc) = 0;
	virtual void OnFrameBegin() = 0;
	virtual void OnFrameEnd() = 0;
};

extern SystemGlobalEnvironment* gEnv;

namespace Torc
{
	namespace Core
	{
		//! This class manages instance of SystemGlobalEnvironment.
		//! This means any instance of a singleton can be queried from here
		//! we have to first initialize this class to make sure other interfaces or managers
		//! are registered. This class itself is also a singleton.
		class SystemEnvironmentInterface
		{
		public:
			static bool StartUp();
			static void Shutdown();
			static SystemEnvironmentInterface* GetInstance();
		};
		

		template<typename T>
		class EnvironmentVariable
		{
			friend class Environment;
			using Type = T;
		public:
			Type* operator->()
			{
				return m_variable;
			}

		private:
			static bool IsInitialized()
			{
				return EnvironmentVariable::m_instance;
			}

			template<typename... Args>
			static EnvironmentVariable<Type>* Init(Args... args)
			{
				EnvironmentVariable::m_instance = new EnvironmentVariable<T>();
				EnvironmentVariable::m_instance->m_variable = new Type(args...);
				return EnvironmentVariable::m_instance;
			}

			static EnvironmentVariable* Get()
			{
				return EnvironmentVariable::m_instance;
			}

			T* m_variable;
			static EnvironmentVariable* m_instance;
		};

		template<typename T>
		EnvironmentVariable<T>* EnvironmentVariable<T>::m_instance = nullptr;

		struct Environment
		{
			template<typename T>
			static EnvironmentVariable<T>* Instance()
			{
				return EnvironmentVariable<T>::Get();
			}

			template<typename T, typename... Args>
			static EnvironmentVariable<T>* GetOrCreate(Args... args)
			{
				bool initialized = EnvironmentVariable<T>::IsInitialized();
				if (!initialized)
				{
					// create an instance and return. Just have to be carefull about thread safety here
					return EnvironmentVariable<T>::Init(args...);
				}

				// since already have an instance, just return it
				return EnvironmentVariable<T>::Get();
			}

			//! NOTE(cagri): There are some potential side effects here that need to be taken care of
			template<typename T>
			static void Destroy()
			{
				// check if there is a valid instance, if so release it
				// otherwise nothing to do really
				if (!EnvironmentVariable<T>::IsInitialized())
				{
					return;
				}
				EnvironmentVariable<T>* evar = EnvironmentVariable<T>::Get();
				T* var = (*evar).m_variable;
				if (var)
				{
					delete var;
					(*evar).m_variable = nullptr;
				}
				delete evar;
				(*evar).m_instance = nullptr;
			}
		};

	}
	
	//! In order to simplify commmunication between listeners and dispatchers,
	//! ComBus a.k.a Communication Bus class will be used as shared interface.
	template<typename T>
	class ComBus
	{
		


	};
}
