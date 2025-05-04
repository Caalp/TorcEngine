//#include "Renderer/GPUObjects/RasterizerState.h"

/*
	
	pass = 
	{
		"name" : "blahBlah",
		"DepthStencilState" : 0,
		"RasterizerState" : 0,
		"BlendState" : 0,
		"RenderTarget" : "$...",
		"DepthBuffer" : "$",
		GlobalResources : [],
	}

	tobj  = {
		TargetPass = ["SkyPass", "Default"],


	}


	struct Texture
	{
		SamplerID
		TextureName
		TextureDesc
	};

	struct Material
	{
		TextureID albedo;
		TextureID normal;
		TextureID displacement;

		shader vs, ps;

		uint64 GetID() const;

	};
	
*/


//namespace gfx
//{
//	const std::map<DepthStencilState::DSSType, DepthStencilDesc> dssDefines =
//	{
//		{	DepthStencilState::DSSType::Default, {
//													//true,
//													//TORC_GFX_DEPTH_WRITE::ALL,
//													//TORC_GFX_COMPARISON_FUNC::LESS,
//													//true,
//													//0xff,
//													//0xff,
//													//{}, // frontface
//													//{} // backface
//												 }
//		},
//
//		{	DepthStencilState::DSSType::Mirror, {
//													//true,
//													//TORC_GFX_DEPTH_WRITE::NONE,
//													//TORC_GFX_COMPARISON_FUNC::LESS,
//													//true,
//													//0xff,
//													//0xff,
//													//{
//													//	TORC_GFX_STENCIL_OP::KEEP, // stencilfailOP
//													//	TORC_GFX_STENCIL_OP::KEEP, // stencilDepthfailOP
//													//	TORC_GFX_STENCIL_OP::REPLACE, // stencilPassOP
//													//	TORC_GFX_COMPARISON_FUNC::ALWAYS // stencilFunc
//													//},
//													//{
//													//	TORC_GFX_STENCIL_OP::KEEP, // stencilfailOP
//													//	TORC_GFX_STENCIL_OP::KEEP, // stencilDepthfailOP
//													//	TORC_GFX_STENCIL_OP::REPLACE, // stencilPassOP
//													//	TORC_GFX_COMPARISON_FUNC::ALWAYS // stencilFunc
//													//}
//												 }
//		},
//
//		{	DepthStencilState::DSSType::DrawReflection, {
//															//true,
//															//TORC_GFX_DEPTH_WRITE::ALL,
//															//TORC_GFX_COMPARISON_FUNC::LESS,
//															//true,
//															//0xff,
//															//0xff,
//															//{
//															//	TORC_GFX_STENCIL_OP::KEEP, // stencilfailOP
//															//	TORC_GFX_STENCIL_OP::KEEP, // stencilDepthfailOP
//															//	TORC_GFX_STENCIL_OP::KEEP, // stencilPassOP
//															//	TORC_GFX_COMPARISON_FUNC::EQUAL // stencilFunc
//															//},
//															//{
//															//	TORC_GFX_STENCIL_OP::KEEP, // stencilfailOP
//															//	TORC_GFX_STENCIL_OP::KEEP, // stencilDepthfailOP
//															//	TORC_GFX_STENCIL_OP::KEEP, // stencilPassOP
//															//	TORC_GFX_COMPARISON_FUNC::EQUAL // stencilFunc
//															//}
//														}
//		},
//
//		{	DepthStencilState::DSSType::NoDoubleBlend, {
//													//true,
//													//TORC_GFX_DEPTH_WRITE::ALL,
//													//TORC_GFX_COMPARISON_FUNC::LESS,
//													//true,
//													//0xff,
//													//0xff,
//													//{
//													//	TORC_GFX_STENCIL_OP::KEEP, // stencilfailOP
//													//	TORC_GFX_STENCIL_OP::KEEP, // stencilDepthfailOP
//													//	TORC_GFX_STENCIL_OP::INCR, // stencilPassOP
//													//	TORC_GFX_COMPARISON_FUNC::EQUAL // stencilFunc
//													//},
//													//{
//													//	TORC_GFX_STENCIL_OP::KEEP, // stencilfailOP
//													//	TORC_GFX_STENCIL_OP::KEEP, // stencilDepthfailOP
//													//	TORC_GFX_STENCIL_OP::INCR, // stencilPassOP
//													//	TORC_GFX_COMPARISON_FUNC::EQUAL // stencilFunc
//													//}
//												 }
//		},
//
//		{	DepthStencilState::DSSType::NoDepthWrite, {
//													/*true,
//													TORC_GFX_DEPTH_WRITE::NONE,
//													TORC_GFX_COMPARISON_FUNC::LESS,
//													true,
//													0xff,
//													0xff,
//													{},
//													{}*/
//												 }
//		},
//
//		{	DepthStencilState::DSSType::LessOrEqual, {
//													/*true,
//													TORC_GFX_DEPTH_WRITE::ALL,
//													TORC_GFX_COMPARISON_FUNC::LESS_EQUAL,*/
//												 }
//		}
//	};
//
//
//	const std::map<BlendState::BlendType, BlendDesc> bsDefines =
//	{
//		{
//			BlendState::BlendType::Default, {
//												false, // blendEnable
//												false, // alphaToCoverage
//												false,  // independentBlend
//												TORC_GFX_BLEND::ONE, // srcBlend
//												TORC_GFX_BLEND::ZERO, // destBlend
//												TORC_GFX_BLEND_OP::ADD, // blendOP
//												TORC_GFX_BLEND::ONE,
//												TORC_GFX_BLEND::ZERO,
//												TORC_GFX_BLEND_OP::ADD,
//												TORC_GFX_COLOR_ENABLE::ALL
//											}
//		},
//
//		{
//			BlendState::BlendType::Transparent, {
//												true, // blendEnable
//												false, // alphaToCoverage
//												false,  // independentBlend
//												TORC_GFX_BLEND::SRC_ALPHA, // srcBlend
//												TORC_GFX_BLEND::INV_SRC_ALPHA, // destBlend
//												TORC_GFX_BLEND_OP::ADD, // blendOP
//												TORC_GFX_BLEND::ONE,
//												TORC_GFX_BLEND::ZERO,
//												TORC_GFX_BLEND_OP::ADD,
//												TORC_GFX_COLOR_ENABLE::ALL
//											}
//		},
//
//		{
//			BlendState::BlendType::AlphaToCoverage, {
//												false, // blendEnable
//												true, // alphaToCoverage
//												false,  // independentBlend
//												TORC_GFX_BLEND::SRC_ALPHA, // srcBlend
//												TORC_GFX_BLEND::INV_SRC_ALPHA, // destBlend
//												TORC_GFX_BLEND_OP::ADD, // blendOP
//												TORC_GFX_BLEND::ONE,
//												TORC_GFX_BLEND::ZERO,
//												TORC_GFX_BLEND_OP::ADD,
//												TORC_GFX_COLOR_ENABLE::ALL
//											}
//		},
//
//		{
//			BlendState::BlendType::NoRenderTargetWrite, {
//												false, // blendEnable
//												false, // alphaToCoverage
//												false,  // independentBlend
//												TORC_GFX_BLEND::ONE, // srcBlend
//												TORC_GFX_BLEND::ZERO, // destBlend
//												TORC_GFX_BLEND_OP::ADD, // blendOP
//												TORC_GFX_BLEND::ONE,
//												TORC_GFX_BLEND::ZERO,
//												TORC_GFX_BLEND_OP::ADD,
//												TORC_GFX_COLOR_ENABLE::NONE
//
//											}
//		},
//
//		{
//			BlendState::BlendType::Additive, {
//												true, // blendEnable
//												false, // alphaToCoverage
//												false,  // independentBlend
//												TORC_GFX_BLEND::ONE, // srcBlend
//												TORC_GFX_BLEND::ONE, // destBlend
//												TORC_GFX_BLEND_OP::ADD, // blendOP
//												TORC_GFX_BLEND::ZERO,
//												TORC_GFX_BLEND::ZERO,
//												TORC_GFX_BLEND_OP::ADD,
//												TORC_GFX_COLOR_ENABLE::ALL
//											}
//		},
//	};
//
//	const std::map<RasterizerState::RasterizerType, RasterizerDesc> rsDefines =
//	{
//		{
//			RasterizerState::RasterizerType::Default, { TORC_GFX_FILL_MODE::SOLID,
//														TORC_GFX_CULL_MODE::BACK,
//														false, // frontCCW
//														0, // depth bias
//														0.0f, // depth bias clamp
//														0.0f, // slopeScaledDepthBias
//														true, // deptpClipEnabled
//														false, //ScissorsEnable
//														false, // multisampleEnabled
//														false, //antialiasedLineEnabled
//													  }
//		},
//		{
//			RasterizerState::RasterizerType::NoCull, { TORC_GFX_FILL_MODE::SOLID,
//													   TORC_GFX_CULL_MODE::NONE,
//													   false, // frontCCW
//													   0, // depth bias
//													   0.0f, // depth bias clamp
//													   0.0f, // slopeScaledDepthBias
//													   true, // deptpClipEnabled
//													   false, //ScissorsEnable
//													   false, // multisampleEnabled
//													   false, //antialiasedLineEnabled
//													 }
//		},
//		{
//			RasterizerState::RasterizerType::CullClockwise, { TORC_GFX_FILL_MODE::SOLID,
//															  TORC_GFX_CULL_MODE::NONE,
//															  true, // frontCCW
//															  0, // depth bias
//															  0.0f, // depth bias clamp
//															  0.0f, // slopeScaledDepthBias
//															  true, // deptpClipEnabled
//															  false, //ScissorsEnable
//															  false, // multisampleEnabled
//															  false, //antialiasedLineEnabled
//															}
//		},
//		{
//			RasterizerState::RasterizerType::Wireframe, { TORC_GFX_FILL_MODE::WIREFRAME,
//															  TORC_GFX_CULL_MODE::NONE,
//															  false, // frontCCW
//															  0, // depth bias
//															  0.0f, // depth bias clamp
//															  0.0f, // slopeScaledDepthBias
//															  true, // deptpClipEnabled
//															  false, //ScissorsEnable
//															  false, // multisampleEnabled
//															  false, //antialiasedLineEnabled
//															}
//		},
//	};
//};