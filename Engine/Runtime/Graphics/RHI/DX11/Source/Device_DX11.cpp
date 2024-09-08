#include "RHI/DX11/Public/Device_DX11.h"
#include "RHI/DX11/Include/base.h"

namespace Torc
{
	namespace RHI
	{
		namespace DX11
		{
			Device_DX11::Device_DX11(ID3D11Device* nativeDevice)
				: m_device(nativeDevice)
			{
			}

			ID3D11Device* Device_DX11::GetNativeObject() const
			{
				return m_device;
			}
		}
	}
}
