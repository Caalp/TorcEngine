#include "Shader.h"

Shader::~Shader()
{
	if (m_metaData)
	{
		delete m_metaData;
	}
	
	// TODO(cagri): inputlayout should live independent from a shader
	// Only VertexShader has InputLayout
	if (m_inputLayout)
	{
		delete m_inputLayout;
	}
}

ShaderMetaData* Shader::CreateNewMetaData()
{
	m_metaData = new ShaderMetaData;
	return m_metaData;
}

ShaderMetaData* Shader::GetMetaData()
{
	return m_metaData;
}

void Shader::SetInputLayout(void* inputLayout)
{
	m_inputLayout = (InputLayout*)inputLayout;
}

InputLayout* Shader::GetInputLayout()
{
	return m_inputLayout;
}

void Shader::SetShaderType(Type shaderType)
{
	m_type = shaderType;
}

Shader::Type Shader::GetShaderType() const
{
	return m_type;
}

void* Shader::GetDesc() const
{
	return nullptr;
}

void Shader::Bind()
{
}