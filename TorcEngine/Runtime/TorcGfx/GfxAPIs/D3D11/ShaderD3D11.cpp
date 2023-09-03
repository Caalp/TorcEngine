
#include "pch.h"
//#pragma once
//
//#include "rr/pch.h"
//#include "rr/public/dx11/DX11Shader.h"
//
//namespace rr
//{
//	DX11Shader::DX11Shader(const char* filepath)
//	{
//		char fullpath[256];
//		strcpy_s(fullpath, SHADER_DIRECTORY);
//		strcat_s(fullpath, filepath);
//
//		size_t len = strlen(fullpath);
//		wchar_t fullpath2[256];
//		MultiByteToWideChar(0, 0, fullpath, len, fullpath2,256);
//		if (strstr(filepath, ".vs"))
//		{
//			m_type = VertexShader;
//		}
//		else if (strstr(filepath, ".ps"))
//		{
//			m_type = PixelShader;
//		}
//		else if (strstr(filepath, ".gs"))
//		{
//			m_type = GeometryShader;
//		}
//		else if (strstr(filepath, ".ds"))
//		{
//			m_type = DomainShader;
//		}
//		else if (strstr(filepath, ".hs"))
//		{
//			m_type = HullShader;
//		}
//		else if (strstr(filepath, ".cs"))
//		{
//			m_type = ComputeShader;
//		}
//		else
//		{
//			// assert unknown shader type
//		}
//		
//		HRESULT hr;
//		// read shader into blob
//		hr = D3DReadFileToBlob(fullpath2, &m_blob);
//		if (FAILED(hr))
//		{
//			// assert failed reading shader
//		}
//		
//		//Create actual shader inside shader database
//
//
//	}
//	const std::unique_ptr<ID3DBlob>& DX11Shader::GetBlob()
//	{
//		// TODO: insert return statement here
//		return {};
//	}
//	const char* DX11Shader::GetName() const
//	{
//		return nullptr;
//	}
//	const ShaderType DX11Shader::GetType() const
//	{
//		return ShaderType();
//	}
//	DX11Shader::~DX11Shader()
//	{
//		delete m_blob;
//	}
//	void DX11Shader::ReadToBlob(const char* filename)
//	{
//	}
//	ShaderReflection::ShaderReflection(ID3DBlob* blob)
//	{
//		HRESULT hr;
//		hr = D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&m_reflector);
//
//		if (FAILED(hr))
//		{
//			// assert
//		}
//
//		m_reflector->GetDesc(&m_shaderDesc);
//	}
//	uint32_t ShaderReflection::GetVersion() const
//	{
//		return uint32_t();
//	}
//	const wchar_t* ShaderReflection::GetCreator() const
//	{
//		return nullptr;
//	}
//}