#include "TerrainClass.h"
//#include "MatHelper.h"
//
//TerrainClass::TerrainClass(Graphics& gfx, DirectX::XMFLOAT3 eyePos,UINT tW, UINT tH, float width, float height) 
//{
//	if (!isStaticallyBinded())
//	{
//		terrainWidth = tW;;
//		terrainHeight = tH;
//		struct Vertex
//		{
//			DirectX::XMFLOAT3 pos;
//			DirectX::XMFLOAT3 normal;
//		};
//
//		UINT vertexCount = tW * tH;
//		UINT triCount = (tW - 1) * (tH - 1) * 2;
//
//		float halfWidth = 0.5f *width;
//		float halfHeight = 0.5f * height;
//		float dx = width / (tH - 1);
//		float dz = height / (tW - 1);
//
//		float du = 1.0f / (tH - 1);
//		float dv = 1.0f / (tW - 1);
//		std::vector<DirectX::XMFLOAT3> v;
//		std::vector<Vertex> vertexData;
//		v.resize(vertexCount);
//
//		std::vector<WORD> indexB;
//
//		for (int j = 0; j < tH; j++)
//		{
//			float z = halfHeight - j * dz;
//			for (int i = 0; i < tW; i++)
//			{
//				float x = -halfWidth + i * dx;
//				v[j*tW + i] = DirectX::XMFLOAT3(x, 0.0f, z);
//
//
//			}
//		}
//
//		indexB.resize(triCount * 3);
//		UINT k = 0;
//
//		for (UINT i = 0; i < tW - 1; ++i)
//		{
//			for (UINT j = 0; j < tH - 1; ++j)
//			{
//				indexB[k] = i * tH + j;
//				indexB[k + 1] = i * tH + j + 1;
//				indexB[k + 2] = (i + 1)* tH + j;
//				indexB[k + 3] = (i + 1) * tH + j;
//				indexB[k + 4] = i * tH + j + 1;
//				indexB[k + 5] = (i + 1) * tH + j + 1;
//				k += 6;
//			}
//		}
//		vertexData.resize(v.size());
//
//		auto getHeight = [](float x, float z)  -> float
//		{
//			return 0.3f*(z*sinf(0.1f*x) + x * cosf(0.1f*z));
//		};
//		auto getHillNormal = [](float x, float z)
//		{
//			// n = (-df/dx, 1, -df/dz)
//			DirectX::XMFLOAT3 n(
//				-0.03f*z*cosf(0.1f*x) - 0.3f*cosf(0.1f*z),
//				1.0f,
//				-0.3f*sinf(0.1f*x) + 0.03f*x*sinf(0.1f*z));
//
//			DirectX::XMVECTOR unitNormal = DirectX::XMVector3Normalize(XMLoadFloat3(&n));
//			XMStoreFloat3(&n, unitNormal);
//
//			return n;
//		};
//
//
//		for (size_t i = 0; i < v.size(); i++)
//		{
//			DirectX::XMFLOAT3 p = v[i];
//
//			p.y = GetHillHeight(p.x, p.z);
//
//			vertexData[i].pos = p;
//
//			vertexData[i].normal = getHillNormal(p.x, p.z);
//			// Color values
//			/*if (p.y < -10.f)
//			{
//				vertexData[i].color = DirectX::XMFLOAT3(1.0f, 0.96f, 0.62f);
//			}
//			else if (p.y < 5.0f)
//			{
//				vertexData[i].color = DirectX::XMFLOAT3(0.48f, 0.77f, 0.46f);
//			}
//			else if (p.y < 12.0f)
//			{
//				vertexData[i].color = DirectX::XMFLOAT3(0.1f, 0.48f, 0.19f);
//			}
//			else if (p.y < 20.0f)
//			{
//				vertexData[i].color = DirectX::XMFLOAT3(0.45f, 0.39f, 0.34f);
//			}
//			else
//			{
//				vertexData[i].color = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
//			}*/
//		}
//		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertexData));
//		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PhongLightingPS.cso"));
//		auto vs = std::make_unique<VertexShader>(gfx, L"PhongLightingVS.cso");
//		auto vsBlob = vs->GetVBlob();
//		AddStaticBind(std::move(vs));
//		AddStaticBind(std::make_unique<IndexBuff>(gfx, indexB));
//		struct MaterialConstantPS
//		{
//
//			DirectX::XMFLOAT4 amb;
//			DirectX::XMFLOAT4 diff;
//			DirectX::XMFLOAT4 spec;
//
//		}matConst;
//
//		matConst.amb = DirectX::XMFLOAT4(0.48f, 0.77f, 0.46f,1.0f);
//		matConst.diff = DirectX::XMFLOAT4(0.48f, 0.77f, 0.46f,1.0f);
//		matConst.spec = DirectX::XMFLOAT4(0.02f, 0.02f, 0.2f,16.0f);
//
//		AddStaticBind(std::make_unique<PSConstBuff<MaterialConstantPS>>(gfx, matConst, 1u));
//
//		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
//		{
//			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
//			{"Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},
//		};
//		/*dx::XMFLOAT4X4 mGridWorld;
//		dx::XMMATRIX I = dx::XMMatrixIdentity();
//		XMStoreFloat4x4(&mGridWorld, I);
//		dx::XMMATRIX modelviewProj = GetTransformation() * gfx.GetCamera();
//
//		dx::XMMATRIX world= GetTransformation();
//
//		dx::XMMATRIX worldInvTranspose = MatHelper::inverseTranspose(world);
//
//
//
//		struct CameraConstBuff
//		{
//			DirectX::XMMATRIX modelView;
//			DirectX::XMMATRIX world;
//			DirectX::XMFLOAT3 eyePosition;
//		} camConst;
//
//		camConst.modelView = DirectX::XMMatrixTranspose(modelviewProj);
//		camConst.world = DirectX::XMMatrixTranspose(world);
//
//		camConst.eyePosition = eyePos;*/
//		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, vsBlob));
//		AddStaticBind(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
//
//		//struct PSMaterialConstant
//		//{
//		//	/*float specularIntensitiy;
//		//	float specularPower;
//		//	float padding;*/
//		//	DirectX::XMFLOAT3 materialColor;
//		//} colorConst;
//		////colorConst.specularIntensitiy = 0.5;
//		////colorConst.specularPower = 32;
//		//colorConst.materialColor = DirectX::XMFLOAT3(0.1f, 0.7f, 0.1f);
//		//AddBind(std::make_unique<PSConstBuff<PSMaterialConstant>>(gfx, colorConst, 1u));
//	}
//	else
//	{
//		SetIndexBufferFromStatic();
//	}
//	//struct VSMaterialConstant
//	//{
//	//	DirectX::XMMATRIX model;
//	//	DirectX::XMMATRIX worldviewProj;
//	//	DirectX::XMFLOAT3 eyePos;
//	//	//float padding;
//	//} VSConst;
//	//VSConst.model = DirectX::XMMatrixTranspose(GetTransformation());
//	//VSConst.worldviewProj = DirectX::XMMatrixTranspose(GetTransformation() * gfx.GetCamera());
//	//VSConst.eyePos = eyePos;
//
//	//AddBind(std::make_unique<VSConstBuff<VSMaterialConstant>>(gfx, VSConst));
//	 AddBind(std::make_unique<TransformationBuffer>(gfx, *this));
//}
//
//DirectX::XMMATRIX TerrainClass::GetTransformation() const
//{
//	return 2*DirectX::XMMatrixIdentity();
//}
//
//
//
//
//
//
//
