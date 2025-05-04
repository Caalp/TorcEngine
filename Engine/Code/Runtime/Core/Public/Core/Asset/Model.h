#pragma once
//#include <string>
//#include <vector>
//#include <memory>
//#include <filesystem>
//#include "Assimp/Importer.hpp"
//#include "Assimp/postprocess.h"
//#include "Assimp/scene.h"
//#include "Node.h"
//#include "Mesh.h"
//
//#define MODEL_PATH "../Compiled/3DX_Build/Models/"
//
//class Graphics;
//struct VertexDataAlignmentInfo
//{
//	uint32_t m_indexCount;
//	uint32_t m_vertexCount;
//	uint32_t m_startIndex;
//	int m_vertexBaseIndex;
//};
//
//// Model class corresponds(equivalent of) aiScene node in assimp part 
//class Model
//{
//	friend class AnimatedCharacter;
//public:
//	Model(Graphics& gfx, 
//		  const std::string& filename, 
//		  unsigned int flags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals | 
//		  aiProcess_FlipUVs | aiProcess_MakeLeftHanded | aiProcess_FlipWindingOrder | aiProcess_LimitBoneWeights);
//	int GetBoneCount();
//	const std::vector<Mesh>& getMeshData()const {
//		return pMesh;
//	}
//	void GetFinalTransforms(std::string clipName, float timePos, Node* node, const DirectX::XMMATRIX& finalTransforms);
//	bool Interpolate(std::string clipName, std::string nodeName, float timePos, DirectX::XMMATRIX& finalTransforms);
//	const std::unique_ptr<Node>& GetRootNode();
//	std::map<int, BoneData> GetBones() const;
//private:
//	void LoadBones(uint32_t meshIndex, uint32_t& boneIndex, const aiMesh& pMesh);
//	std::unique_ptr<Node> ParseNode(int& nextId, const aiNode& node, const DirectX::XMMATRIX& parentTransform);
//private:
//	std::unique_ptr<Node> pRootNode;
//	std::map<std::string, const Node*> nodes;
//	std::vector<Mesh> pMesh;
//	std::map<std::string, AnimationClip> anims;
//	std::map<int, BoneData> bones;
//	std::map<std::string, int> boneToIndex;
//	std::vector<DirectX::XMMATRIX> finalTransforms;
//};