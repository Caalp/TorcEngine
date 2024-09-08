#pragma once
#include <RHI/RHI.Public/Device.h>

struct ID3D11Device;

namespace Torc
{
	namespace RHI
	{
		namespace DX11
		{
			class Device_DX11 : public RHI::Device
			{
			public:
				Device_DX11(ID3D11Device* nativeDevice);
				ID3D11Device* GetNativeObject() const;

			private:
				ID3D11Device* m_device;
			};
		}
	}
}
