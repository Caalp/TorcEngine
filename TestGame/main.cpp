#define _CRTDBG_MAP_ALLOC

#include <Core/Application.h>
#include <Core/FileSystem/FileSystem.h>
#include <Core/Logging/Logger.h>
#include <Core/TorcSystem/ISystem.h>
#include <GameCore/Components/TransformComponent.h>

#include <variant>
#include <random>
#include <chrono>
#include <Windows.h>

#ifdef USE_D3D11_GFX_BACKEND
// include the dll here

#else
// print out and error here    
#endif

//struct debug_state
//{
//	debug_state() {}
//	~debug_state() { _CrtDumpMemoryLeaks(); }
//};
//
//#pragma init_seg(compiler)
//debug_state ds;

//static void PrintDebug(const char* str, ...)
//{
//	char dbg[256];
//
//	va_list args;
//	va_start(args, str);
//	vsnprintf(dbg, _countof(dbg), str, args);
//	va_end(args);
//
//	OutputDebugStringA(dbg);
//}

//void Main()
//{
	//gfx::ITorcGfxBackend* gfxBackend = gEnv->rr->GetGFXBackend();
	//struct Vertex
	//{
	//	DirectX::XMFLOAT3 pos;
	//};

	//std::vector<Vertex> vertices;
	//vertices.resize(24);

	//constexpr float side = 1.0f;

	//vertices[0].pos = { -side,-side,-side };// 0 near side
	//vertices[1].pos = { side,-side,-side };// 1
	//vertices[2].pos = { -side,side,-side };// 2
	//vertices[3].pos = { side,side,-side };// 3
	//vertices[4].pos = { -side,-side,side };// 4 far side
	//vertices[5].pos = { side,-side,side };// 5
	//vertices[6].pos = { -side,side,side };// 6
	//vertices[7].pos = { side,side,side };// 7
	//vertices[8].pos = { -side,-side,-side };// 8 left side
	//vertices[9].pos = { -side,side,-side };// 9
	//vertices[10].pos = { -side,-side,side };// 10
	//vertices[11].pos = { -side,side,side };// 11
	//vertices[12].pos = { side,-side,-side };// 12 right side
	//vertices[13].pos = { side,side,-side };// 13
	//vertices[14].pos = { side,-side,side };// 14
	//vertices[15].pos = { side,side,side };// 15
	//vertices[16].pos = { -side,-side,-side };// 16 bottom side
	//vertices[17].pos = { side,-side,-side };// 17
	//vertices[18].pos = { -side,-side,side };// 18
	//vertices[19].pos = { side,-side,side };// 19
	//vertices[20].pos = { -side,side,-side };// 20 top side
	//vertices[21].pos = { side,side,-side };// 21
	//vertices[22].pos = { -side,side,side };// 22
	//vertices[23].pos = { side,side,side };// 23

	//std::vector<uint16_t> indices =
	//{
	//		0,2,1,    2,3,1,
	//		4,5,7,    4,7,6,
	//		8,10, 9,  10,11,9,
	//		12,13,15, 12,15,14,
	//		16,17,18, 18,17,19,
	//		20,23,21, 20,22,23
	//};
	//Renderer* rr = gEnv->rr;
	//static bool isInitialized = false;

	//BufferHandle vb;
	//BufferHandle ib;
	//BufferHandle objectCBHandle;
	//BufferHandle cameraCBHandle;
	//ShaderHandle ps;
	//ShaderHandle vs;
	//if (!isInitialized)
	//{
	//	static std::string engineRoot = Torc::Platform::GetEngineRootDirectory();
	//	static std::string shaderDirectory = engineRoot + "\\TorcEngine\\Shaders\\";
	//	ps = rr->CompileShader((shaderDirectory + "BasicPS.hlsl").c_str(), Shader::Type::PS);
	//	vs = rr->CompileShader((shaderDirectory + "BasicVS.hlsl").c_str(), Shader::Type::VS);

	//	gfx::BufferDesc vbeDesc{};
	//	vbeDesc.vb.numBuffers = 1;
	//	vbeDesc.vb.startSlot = 0;
	//	vbeDesc.vb.stride = sizeof(Vertex);
	//	vbeDesc.bindFlags = gfx::TORC_GFX_RESOURCE_BIND_FLAG::BIND_VERTEX_BUFFER;

	//	gfx::SubResourceData initData{};
	//	initData.sysMem = vertices.data();
	//	initData.byteWidth = (uint32)vertices.size() * sizeof(Vertex);
	//	initData.structureByteStride = (uint32)sizeof(Vertex);
	//	vbeDesc.data = initData;

	//	vb = rr->CreateBuffer(vbeDesc);

	//	gfx::BufferDesc ibeDesc{};

	//	ibeDesc.ib.format = gfx::TORC_GFX_RESOURCE_DATA_FORMAT::FORMAT_R16_UINT;
	//	ibeDesc.ib.offset = 0;
	//	ibeDesc.bindFlags = gfx::TORC_GFX_RESOURCE_BIND_FLAG::BIND_INDEX_BUFFER;

	//	gfx::SubResourceData initData2{};
	//	initData2.sysMem = indices.data();
	//	initData2.byteWidth = (uint32)indices.size() * sizeof(uint16_t);
	//	initData2.structureByteStride = sizeof(uint16_t);
	//	ibeDesc.data = initData2;

	//	ib = rr->CreateBuffer(ibeDesc);

	//	rr->BindPrimitiveTopology(gfx::TORC_GFX_PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//	struct TransformationConstantBuffer
	//	{
	//		math::Matrix4x4f world;
	//		math::Matrix4x4f worldInverseTranspose;
	//	};

	//	TransformationConstantBuffer objectConstantBuffer;
	//	objectConstantBuffer.world = math::MatrixIdentity<math::Matrix4x4f>();
	//	objectConstantBuffer.worldInverseTranspose = math::MatrixIdentity<math::Matrix4x4f>();

	//	gfx::BufferDesc objCBDesc{};
	//	objCBDesc.usage = gfx::TORC_GFX_RESOURCE_USAGE::USAGE_GPU_READ_CPU_WRITE;
	//	objCBDesc.cpuAccessFlags = gfx::TORC_GFX_CPU_ACCESS_FLAG::CPU_ACCESS_WRITE;
	//	objCBDesc.cb.cbType = gfx::BufferDesc::ConstantBufferType::VS;
	//	objCBDesc.bindFlags = gfx::TORC_GFX_RESOURCE_BIND_FLAG::BIND_CONSTANT_BUFFER;
	//	objCBDesc.cb.startSlot = 0;
	//	objCBDesc.cb.numBuffers = 1;

	//	gfx::SubResourceData InitData3{};
	//	InitData3.sysMem = &objectConstantBuffer;
	//	InitData3.byteWidth = sizeof(TransformationConstantBuffer);
	//	InitData3.structureByteStride = 0u;
	//	objCBDesc.data = InitData3;

	//	objectCBHandle = rr->CreateBuffer(objCBDesc);

	//	struct CameraConstantBuffer
	//	{
	//		math::Matrix4x4f viewMatrix;
	//		math::Matrix4x4f projectionMatrix;
	//		math::Matrix4x4f viewProjMatrix;
	//		math::Vec3f cameraPosition;
	//		float padding;

	//	};

	//	CameraConstantBuffer cameraConstantBuffer;
	//	static Camera staticCamera;
	//	staticCamera.SetCameraLens(0.25f * 3.1415926535f, 1280 / 720.0f, 1.0f, 1000.0f);
	//	cameraConstantBuffer.cameraPosition = staticCamera.GetPosition();
	//	cameraConstantBuffer.viewMatrix = staticCamera.GetViewMatrix();
	//	cameraConstantBuffer.projectionMatrix = staticCamera.GetProjectionMatrix();
	//	math::MatrixMultiply(objectConstantBuffer.world, cameraConstantBuffer.viewMatrix, &cameraConstantBuffer.viewProjMatrix);
	//	math::MatrixMultiply(cameraConstantBuffer.viewProjMatrix, cameraConstantBuffer.projectionMatrix, &cameraConstantBuffer.viewProjMatrix);
	//	math::MatrixTranspose(cameraConstantBuffer.viewProjMatrix, &cameraConstantBuffer.viewProjMatrix);

	//	gfx::BufferDesc cbd2Desc{};
	//	cbd2Desc.usage = gfx::TORC_GFX_RESOURCE_USAGE::USAGE_GPU_READ_CPU_WRITE;
	//	cbd2Desc.cpuAccessFlags = gfx::TORC_GFX_CPU_ACCESS_FLAG::CPU_ACCESS_WRITE;
	//	cbd2Desc.cb.cbType = gfx::BufferDesc::ConstantBufferType::VS;
	//	cbd2Desc.bindFlags = gfx::TORC_GFX_RESOURCE_BIND_FLAG::BIND_CONSTANT_BUFFER;
	//	cbd2Desc.cb.startSlot = 1;
	//	cbd2Desc.cb.numBuffers = 1;

	//	gfx::SubResourceData InitData4{};
	//	InitData4.sysMem = &cameraConstantBuffer;
	//	InitData4.byteWidth = sizeof(CameraConstantBuffer);
	//	InitData4.structureByteStride = 0u;
	//	cbd2Desc.data = InitData4;

	//	cameraCBHandle = rr->CreateBuffer(cbd2Desc);

	//	rr->BindBuffer(ib);
	//	rr->BindBuffer(vb);
	//	rr->BindBuffer(objectCBHandle);
	//	rr->BindBuffer(cameraCBHandle);
	//	rr->BindShader(vs);
	//	rr->BindShader(ps);

	//	isInitialized = true;
	//}
	//
	//math::Vec4f bc;
	//bc.x = 0.2f;
	//bc.y = 0.2f;
	//bc.z = 0.2f;
	//bc.w = 1.0f;
	//rr->ClearBackBuffer(bc);

	//gfxBackend->DrawIndexed((uint32)indices.size(), 0u, 0);
	//rr->EndFrame();
//}

//static std::vector<IGPUResource*> m_gpuResources;

#include <FreeImage/FreeImage.h>
#include <Core/Singleton/Singleton.h>
#include <Asset/Asset.h>

void Main2()
{

	static bool run = true;

	if (run)
	{
		std::string filepath = "Assets/wall.bmp";
		TORC_HANDLE file = fs::OpenFile(filepath.c_str(), FileAccessMode::Access_Read, FileShareMode::Share_None, FileCreationFlag::Open_Existing);

		if (fs::IsOpen(file))
		{
			TE_Warning(LogChannel::LC_Core, "Found!!");
			fs::CloseFile(file);
		}
		else
		{
			TE_Warning(LogChannel::LC_Core, "Not Found!!");
		}

		run = false;
	}
}

void Main3()
{

	static bool run = true;

	if (run)
	{
		std::string filepath = "Assets/wall.bmp";
		TE::AssetInfo info;
		info.m_relativePath = filepath;
		info.m_type = TE::Asset::Type::Image;
		TE::ImageAssetLoader imageLoader;
		uint8* data = imageLoader.Load(info);

		if (data != nullptr)
		{
			TE_Warning(LogChannel::LC_Core, "Image is loaded");
		}
		else
		{
			TE_Warning(LogChannel::LC_Core, "Image is not loaded");
		}

		delete data;
		run = false;
	}
}

struct dummy
{

};

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	/*_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);*/

	// launch the engine in a separate thread
	AppCreateParams params = {};
	params.cmdLineArgs = cmdline;

	params.wndWidth = 1280;
	params.wndHeight = 720;
	params.wndCaption = "TestGame";
	Application app;
	app.Initialize(params);

	app.Run(&Main3);

	app.Release();

	// an object with
	// PS: C:\\Users\\calp\\source\\repos\\TorcEngine\\TorcEngine\\Shaders\\BasicPS.hlsl
	// PS: C:\\Users\\calp\\source\\repos\\TorcEngine\\TorcEngine\\Shaders\\BasicVS.hlsl
	return 0;
}