#pragma once

#include <vector>

class RenderGraph;
class RenderQueuePass;
class IGPUResource;
struct ResourceHandle;
struct DrawCommand;

class Step
{
public:
	Step(const char* targetPassName);
	Step(const Step&) = default;
	void AddBindable(ResourceHandle bindable);
	void AddBindable(IGPUResource* bindable);
	void SetDrawCommand(DrawCommand* drawCmd);
	void Submit();
	void Link(RenderGraph* rg);
	void Bind() const;
	void Draw() const;
	const char* GetTargetPassName() const;
	bool IsLinked() const;
private:
	bool m_isLinked;
	const char* m_targetPassName;
	RenderQueuePass* m_targetPass;
	std::vector<IGPUResource*> m_bindables;
	DrawCommand* m_drawCommand;
};