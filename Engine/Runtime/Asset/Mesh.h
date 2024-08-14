//#pragma once
//#include <string>
//#include <vector>
//#include <map>
//#include "assimp/Importer.hpp"
//#include "assimp/postprocess.h"
//#include "assimp/scene.h"
//#include "Drawable.h"
//
//class Graphics;
//class Technique;
//class RenderGraph;
//class Drawable;
//
//struct Vertices
//{
//	DirectX::XMFLOAT3 pos;
//	//DirectX::XMFLOAT3 normal;
//	DirectX::XMFLOAT3 texCoordinates;
//	DirectX::XMFLOAT4 weights;
//	BYTE boneIndices[4];
//};
//
//struct TextureData
//{
//	//unsigned int id;
//	TextureData(uint8_t t, std::string p) :type(t), path(p) {}
//	uint8_t type;
//	std::string path;
//};
//
//struct BoneVertexWeightInfo
//{
//	uint32_t boneVertexID; //vertexid where bone has affect on
//	float boneVertexWeight;
//};
//
//struct BoneData
//{
//	DirectX::XMMATRIX offsetMatrix; // Transforms mesh space to bone space
//	DirectX::XMMATRIX finalTransform;
//};
//
//class Mesh
//{
//public:
//	Mesh() = default;
//	void ParseMesh(const aiMesh& mesh, const aiMaterial* const* pMaterials, std::string texIncludeDir);
//	void InitDrawable(Graphics& gfx, const Technique& tech, std::string name, uint32_t id);
//	void Submit(size_t channel);
//	void LinkTechnique(RenderGraph& rg);
//	void SetName(std::string name);
//	std::string GetName() const;
//private:
//	void InitBuffers(Graphics& gfx);
//public:
//	Drawable db;
//	std::string derivedNodeName;
//	std::vector<Vertices> m_vertices;
//	std::vector<WORD> indices;
//	std::vector<TextureData> textures;
//};