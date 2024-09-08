#pragma once
#include "RHI/DX11/Include/base.h"
#include <RHI/RHI.Public/DeviceContext.h>

namespace Torc
{
	namespace RHI
	{
		namespace DX11
		{
			class DeviceContext_DX11 : public RHI::DeviceContext
			{
			public:
				DeviceContext_DX11(ID3D11DeviceContext* deviceContext);
				ID3D11DeviceContext* GetNativeObject() const;

			private:
				ID3D11DeviceContext* m_deviceContext;
			};
		}
	}
}
