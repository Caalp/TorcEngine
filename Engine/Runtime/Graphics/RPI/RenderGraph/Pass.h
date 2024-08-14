#pragma once
#include "Sink.h"
#include "Source.h"
#include "RDI/RDIShared/TorcGfxTypes.h"

#include <unordered_map>
#include <map>

//class Sink;
//class Source;

enum class PassSlotUsage
{
	Shader,		// resource in the slot can be bind as shader resource view
	Buffer,		// resource is a buffer
	RenderTarget,
	DepthStencil,
};

enum class PassSlotType
{
	Input, // resource bind to this slot only used as input 
	Output, // pass outputs to resource bind to this slot
	InputOutput // resource read and written by the pass
};

struct PassAttachment;

class PassSlot
{
public:

	bool m_isBinded;
	PassSlotUsage m_slotUsage;
	PassSlotType m_slotType;

	// TODO(cagri): replace these strings with something more efficient
	TEStd::string m_slotName;
	PassAttachment* m_currentBinding;
};

struct PassConnection
{
	TEStd::string m_localSlotName;

	TEStd::string m_refSlotName;
	TEStd::string m_refPassName;
};

//struct Technique
//{
//	std::string m_name;
//	std::string m_shader;
//
//	// dss
//	// rs
//	// bs
//
//	// shader entry points ?? 
//
//};

struct DrawItem
{

};

struct DrawPacket
{

};

struct DrawList
{

};

class PassData
{
	TEStd::string m_infoType;
	TEStd::string m_techniquePath;
	TEStd::string m_targetViewName;
	TEStd::string m_targetListName;
};

class PassTemplate
{
public:

	/*
	* Optional pass information that can be provided with the template. This structure holds some data that can be 
	* used for later stage of the pipeline to submit the pass to target draw list or view, retrive technique to be used
	* etc.	
	*/
	PassData m_passInfo;

	/*
	* Name of the pass template. This name will be stored and will provide a way to access to the pass template from
	* PassInterfaceSystem using this name.
	*/
	TEStd::string m_templateName;

	/*
	* Name of the pass class that would be created. Each pass class has static Create function and 
	* these classes are registered to PassSystemInterface with a unique name. This name will be used to 
	* retrieve Create function to create the target pass.
	*/
	TEStd::string m_passClassName;

	/*
	* PassConnections have the information of which slot is connected to what slot and
	* where connected slot's resource resides, mainly which pass slot is coming from.
	*/
	std::vector<PassConnection> m_connections;

	// NOTE(cagri): maybe can be replaced by fixed_vector
	std::vector<PassSlot> m_slots;
};

enum class PassAttachmentType
{
	Buffer,
	Image
};

struct PassDescriptor
{
	std::string m_passTemplate; // name of the pass template
	std::string m_passName;
};

class Pass;

typedef PassTemplate(*PassTemplateCreateFunc)();
typedef Pass*(*PassCreateFunc)(const PassDescriptor&);

class PassSystemInterface
{
public:
	static PassSystemInterface* Get()
	{
		static PassSystemInterface m_instance;
		return &m_instance;
	}

	void AddPassTemplate(TEStd::RefCountedPtr<PassTemplate>& passTemplate)
	{
		if (m_passTemplates.count(passTemplate->m_templateName) == 0)
		{
			m_passTemplates.insert(m_passTemplates.end(), { passTemplate->m_templateName, passTemplate});
		}
	}

	void AddPassCreator(TEStd::string name, PassCreateFunc creatorFunc)
	{
		if (m_passCreateFunctions.count(name) != 0)
		{
			return;
		}
		m_passCreateFunctions.insert(m_passCreateFunctions.end(), { name, creatorFunc });
	}

	void AddPass(TE::Name name, TEStd::RefCountedPtr<Pass>& pass)
	{
		if (m_passes.count(name) == 0)
		{
			m_passes.insert(m_passes.end(), { name, pass });
		}
	}

	void RegisterPassTemplateCreateFunc(std::string name, PassTemplateCreateFunc func)
	{
		if (m_passTemplateCreateFunctions.count(name) == 0)
		{
			m_passTemplateCreateFunctions.insert(m_passTemplateCreateFunctions.end(), { name, func });
		}

		TEStd::RefCountedPtr<PassTemplate> passTemp = std::make_shared<PassTemplate>(func());
		AddPassTemplate(passTemp);
	}

	TEStd::RefCountedPtr<Pass> GetPassByName(TEStd::string name)
	{
		auto iter = m_passes.find(name);
		if (iter != m_passes.end())
		{
			return iter->second;
		}
		return nullptr;
	}

	TEStd::RefCountedPtr<PassTemplate> GetPassTemplateByName(TEStd::string name)
	{
		auto iter = m_passTemplates.find(name);
		if (iter != m_passTemplates.end())
		{
			return iter->second;
		}
		return nullptr;
	}

private:
	std::unordered_map<TE::Name, TEStd::RefCountedPtr<PassTemplate>> m_passTemplates;
	std::unordered_map<TE::Name, TEStd::RefCountedPtr<Pass>> m_passes;
	std::unordered_map<TE::Name, PassTemplateCreateFunc> m_passTemplateCreateFunctions;
	std::unordered_map<TE::Name, PassCreateFunc> m_passCreateFunctions;
};

// Attachments are created and represents the 
struct PassAttachment
{
	PassAttachmentType m_type; // attachment type should be compatible with slot
	PassSlotType m_slotType; // type of slot that attachment is attached to
	PassSlotUsage m_slotUsage; // type of slot that attachment is attached to
	uint64 m_resourceId; // resource id that will be bind to the pipeline
};

struct PassAttachmentBinding
{
	TEStd::string m_asset;
	PassAttachment* m_attachment;
};

// we have bunch of passes stored here 
// we can also create a pass manager which can be a singleton, that takes a library and
// during runtime can do passslot-attachment linkings
class PassLibrary
{
public:

private:

};

class PassManager
{
public:

private:

};

static const std::map<std::string, std::vector<std::string>> s_directoryLookup = { 
	{"tex", {"TorcEngine/Assets"}} 
};

struct ImageLoadDesc
{
	std::string filepath = "";
	bool m_generateMips = true;
	gfx::TORC_GFX_RESOURCE_USAGE m_usage = gfx::TORC_GFX_RESOURCE_USAGE::USAGE_GPU_READ_AND_WRITE;
	gfx::TORC_GFX_CPU_ACCESS_FLAG m_accessFlags = gfx::TORC_GFX_CPU_ACCESS_FLAG::NO_ACCESS;
	gfx::TORC_GFX_RESOURCE_BIND_FLAG m_bindFlags = gfx::TORC_GFX_RESOURCE_BIND_FLAG::BIND_SHADER_RESOURCE;

	uint8* m_data = nullptr;
	uint32 m_dataSize;
};


//class AssetLibrary
//{
//public:
//
//private:
//};
//
//class AssetLoader
//{
//public:
//	ImageAsset* Submit(ImageLoadDesc imgAsset)
//	{
//		ImageAsset* img = new ImageAsset();
//		
//		// check image if already exists
//		m_imageAssetsInLoad[img] = imgAsset;
//
//	}
//
//	void OnLoaded(Asset* asset)
//	{
//
//	}
//
//private:
//	std::map<ImageAsset*, ImageLoadDesc> m_imageAssetsInLoad;
//
//};

class Pass
{
public:
	Pass() = default;
	Pass(const char* passName);
	Pass(const PassDescriptor& descriptor);

	void RegisterSlot(const PassSlot& slot);
	PassSlot* GetSlotByName(const char* slotName);
	const std::string& GetName() const;

	virtual void Reset() {};
	virtual void Execute() {};

	void BeginFrame() {}
	void EndFrame() {}

protected:
	bool m_isLinked;
	std::string m_passName;
	PassTemplate* m_template; // template this pass is created from
	PassDescriptor m_descriptor;

private:
	void BeginFrameInternal() {}
	void EndFrameInternal() {}
};

// kind of RenderQueuePass ??
class RenderPass : public Pass
{
public:
	RenderPass(const PassDescriptor& desc)
		: Pass(desc)
	{
	}
};

class RasterPass : public RenderPass
{
public:
	RasterPass(const PassDescriptor& desc)
		: RenderPass(desc)
	{
	}
	
	virtual void Reset() override {};
	virtual void Execute() override {};
};

class ComputePass : public RenderPass
{
public:
	ComputePass(const PassDescriptor& desc)
		: RenderPass(desc)
	{
	}
	virtual void Reset() override {};
	virtual void Execute() override {};
};


class RenderPipeline
{
public:

};

class Scene
{
public:
	std::vector<RenderPipeline> m_renderPipelines;
};
