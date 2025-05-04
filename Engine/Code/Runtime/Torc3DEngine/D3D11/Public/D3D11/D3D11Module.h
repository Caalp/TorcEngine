#pragma once
#include <Core/Memory/Memory_defs.h>
#include <Core/Module/Module.h>

namespace Torc
{
	class D3D11Module : public Module
	{
	public:
		D3D11Module() = default;

		void Startup() override {}
		void Shutdown() override {}
	private:

	};
}

// TORC_API
extern "C" Torc::Module* CreateModule_D3D11Module() { return torc_new Torc::D3D11Module(); }
