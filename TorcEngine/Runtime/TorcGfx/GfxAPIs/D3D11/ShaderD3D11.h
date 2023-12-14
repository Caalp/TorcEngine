#pragma once
#include "D3D11Common.h"

class ShaderD3D11
{
public:
private:
	union
	{
		ID3D11PixelShader* m_pixelShader;
		ID3D11VertexShader* m_vertexShader;
	};
	void* m_byteCode;
	size_t m_byteCodeLength;
};
