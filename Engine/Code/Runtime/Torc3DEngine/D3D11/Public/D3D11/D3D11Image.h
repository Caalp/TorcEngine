#pragma once
#include "D3D11Base.h"
#include <RHI/Image.h>

namespace Torc
{
	namespace RHI
	{
		namespace D3D11
		{
			class D3D11Image2D : public RHI::Image
			{
			public:
				void SetResource(void* pResource) override { m_tex2D = (ID3D11Texture2D*)pResource; };
				ID3D11Texture2D* GetResource() { return m_tex2D; }
			private:

				ID3D11Texture2D* m_tex2D;
			};

			class D3D11Image3D : public RHI::Image
			{
			public:
			private:
				ID3D11Texture3D* m_tex3D;
			};
		}
	}
}
