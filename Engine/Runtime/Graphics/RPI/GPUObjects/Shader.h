#pragma once
#include "RPI/IGPUResource.h"

#include <unordered_map>

class InputLayout;

struct ShaderMetaData
{
	int32 type;
	std::unordered_map<std::string, uint32_t> resourceMap; // maps resource name to slot
	void* byteCode;
	size_t byteCodeSize;
	std::string name;
	size_t hash;
};

class Shader : public IGPUResource
{
public:
	enum Type : int32
	{
		PS,
		VS,
		GS,
		HS,
		DS
	};

	~Shader();
	ShaderMetaData* CreateNewMetaData();
	ShaderMetaData* GetMetaData();
	void SetInputLayout(void* inputLayout);
	InputLayout* GetInputLayout();
	void SetShaderType(Type shaderType);
	Shader::Type GetShaderType() const;
	
	virtual void* GetDesc() const override;
	virtual void Bind() override;

private:
	Shader::Type m_type;
	InputLayout* m_inputLayout;
	ShaderMetaData* m_metaData;
};