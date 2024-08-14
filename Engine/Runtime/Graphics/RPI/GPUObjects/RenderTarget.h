#pragma once
#include "RPI/IGPUResource.h"

class Texture;
class DepthStencilBuffer;

class RenderTarget : public IGPUResource
{
public:
	static RenderTarget* Create(const gfx::RenderTargetDesc& desc);

	RenderTarget(const gfx::RenderTargetDesc& desc);
	~RenderTarget();
	virtual void* GetDesc() const override;
	virtual void Bind() override;

	virtual Texture* GetShaderResource() { return nullptr; }
	bool IsShaderResource() const;
	void SetDepthStencilBuffer(DepthStencilBuffer* dssView);
	DepthStencilBuffer* GetDepthStencilBuffer();
	bool HasMatchingDepthStencilBuffer() const;
protected:
	gfx::RenderTargetDesc m_desc;
	DepthStencilBuffer* m_depthStencilBuffer;
};

class ShaderResourceRenderTarget final : public RenderTarget
{
public:
	ShaderResourceRenderTarget(const gfx::RenderTargetDesc& desc);
	~ShaderResourceRenderTarget();
	void BindAsShaderResource();
	void SetShaderResource(Texture* srvTex);
	virtual Texture* GetShaderResource() override { return m_texture; }
private:
	Texture* m_texture;
};