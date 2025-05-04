#pragma once
#include "D3D11Common.h"

struct ID3D11PixelShader;
struct ID3D11VertexShader;

class D3D11Shader
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
