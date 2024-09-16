#pragma once
#include "RHI/DX11/Include/base.h"
#include <RHI/RHI.Public/Image.h>

namespace Torc
{
	namespace RHI
	{
		namespace DX11
		{
			class Image2D_DX11 : public Image
			{
			public:
				void SetResource(void* pResource) override { m_tex2D = (ID3D11Texture2D*)pResource; };
			private:

				ID3D11Texture2D* m_tex2D;
			};

			class Image3D_DX11 : public Image
			{
			public:
			private:
				ID3D11Texture3D* m_tex3D;
			};
		}
	}
}
