#pragma once

namespace Torc
{
	class Module
	{
	public:
		typedef Module* (*InitFunc)(const char*);
		Module(const char* moduleName);
		virtual ~Module() = default;

		const char* GetModuleName() const;

		virtual void Startup() = 0;
		virtual void Shutdown() = 0;

	private:
		const char* m_moduleName;
	};
}
