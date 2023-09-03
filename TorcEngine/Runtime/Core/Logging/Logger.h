#pragma once

namespace Torc
{
	class Logger
	{
	public:
		enum LogChannel
		{
			LOG_LISTEN_NONE = 0,
			LOG_LISTEN_INFO = 1,
			LOG_LISTEN_WARNING = 2,
			LOG_LISTEN_ERROR = 4,
			LOG_LISTEN_ALL = 7,
			COUNT
		};
		
		class Listener
		{
		public:
			virtual void LogError(const char* msg) = 0;
			virtual void LogInfo(const char* msg) = 0;
			virtual void LogWarning(const char* msg) = 0;

			// In the begining listens for nothing 
			// listenerType should be unique string for each type of listener
			// it is used for identifying type of listener and making sure listener queue populated 
			// with only unique listeners so, each listener in the queue is unique. 
			// In case of dublications registeration will fail and it will assert.
			Listener(const char* listenerType, LogChannel channel = LOG_LISTEN_NONE) :
				m_listenerType(listenerType)
				, m_channelToListen(channel)
			{}

			inline LogChannel GetChannels() const
			{
				return m_channelToListen;
			}
			const char* GetListenerType() const
			{
				return m_listenerType.c_str();
			}
		private:
			LogChannel m_channelToListen;
			std::string m_listenerType;
		};

		Logger(const char* file, const char* function, int line, const char* msg);
		Logger(const char* msg, ...);
		~Logger() = default;
		static void Initialize();
		static void Shutdown();

		static void Register(std::unique_ptr<Listener> listener);
		static void Unregister(std::unique_ptr<Listener> listener);

		void LogInfo();
		void LogError();
		void LogWarning();
		inline const char* MessageString()
		{
			return m_msg;
		}
	private:
		char m_msg[1024];
	};

	class LogToDebugWindow final : public Logger::Listener
	{
	public:
		// currently just pipe all outputs to std 
		LogToDebugWindow(Logger::LogChannel channel = Logger::LOG_LISTEN_ALL) : Listener("LogToDebugWindow", channel) {}
		void LogError(const char* msg) override;
		void LogInfo(const char* msg) override;
		void LogWarning(const char* msg) override;
	};

	class LogToFile final : public Logger::Listener
	{
	public:
		LogToFile(const char* file, Logger::LogChannel channel = Logger::LOG_LISTEN_ALL) : Listener("LogToFile", channel)
		{

		}

		void LogError(const char* msg) override
		{
			//std::cout << "[ERROR] " << msg << std::endl;
		}
		void LogInfo(const char* msg) override
		{
			//std::cout << "[INFO] " << msg << std::endl;
		}
		void LogWarning(const char* msg) override
		{
			//std::cout << "[WARNING] " << msg << std::endl;
		}
	private:
		// File here
	};
}