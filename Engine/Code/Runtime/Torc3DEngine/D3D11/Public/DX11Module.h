#pragma once
#include <Core/Memory/Memory_defs.h>
#include <Core/Module/Module.h>

namespace Torc
{
	class DX11Module : public Module
	{
	public:
		void ActivateModule() override {}
	private:

	};
}

// TORC_API
extern "C" Torc::Module* CreateModule_DX11Module() { return torc_new Torc::DX11Module(); }
