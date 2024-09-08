#include "RHI/DX11/Public/DeviceContext_DX11.h"

namespace Torc
{
	namespace RHI
	{
		namespace DX11
		{
			DeviceContext_DX11::DeviceContext_DX11(ID3D11DeviceContext* deviceContext)
				: m_deviceContext(deviceContext)
			{
			}

			ID3D11DeviceContext* DeviceContext_DX11::GetNativeObject() const
			{
				return m_deviceContext;
			}
		}
	}
}
