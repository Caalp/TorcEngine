#include "Asset/Mesh.h"
//#include "additional_headers.h"
//
//void Mesh::ParseMesh(const aiMesh& mesh, const aiMaterial* const* pMaterials, std::string texIncludeDir)
//{
//	//vertices.resize(mesh.mNumVertices);
//	for (unsigned int i = 0; i < mesh.mNumVertices; i++)
//	{
//		Vertices vertices;
//		vertices.pos.x = mesh.mVertices[i].x;
//		vertices.pos.y = mesh.mVertices[i].y;
//		vertices.pos.z = mesh.mVertices[i].z;
//
//		//if (mesh.mNormals != NULL)
//		//{
//		//	vertices.normal.x = mesh.mNormals[i].x;
//		//	vertices.normal.y = mesh.mNormals[i].y;
//		//	vertices.normal.z = mesh.mNormals[i].z;
//		//}
//		if (mesh.mTextureCoords[0])
//		{
//			vertices.texCoordinates.x = mesh.mTextureCoords[0][i].x;
//			vertices.texCoordinates.y = mesh.mTextureCoords[0][i].y;
//			vertices.texCoordinates.z = (float)mesh.mMaterialIndex;
//		}
//		else
//		{
//			vertices.texCoordinates = DirectX::XMFLOAT3(0.0f, 0.0f, (float)mesh.mMaterialIndex);
//		}
//		vertices.weights.x = 0.0f;
//		vertices.weights.y = 0.0f;
//		vertices.weights.z = 0.0f;
//		vertices.weights.w = 0.0f;
//
//		vertices.boneIndices[0] = 0;
//		vertices.boneIndices[1] = 0;
//		vertices.boneIndices[2] = 0;
//		vertices.boneIndices[3] = 0;
//		m_vertices.push_back(vertices);
//	}
//	for (unsigned int i = 0; i < mesh.mNumFaces; i++)
//	{
//		aiFace face = mesh.mFaces[i];
//		for (unsigned int j = 0; j < face.mNumIndices; j++)
//			indices.push_back(face.mIndices[j]);
//	}
//	std::string pathEntry = texIncludeDir;
//	aiString textureName;
//	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_UNKNOWN))
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), textureName);
//		textures.emplace_back(aiTextureType_SPECULAR, pathEntry + textureName.C_Str());
//		textureName.Clear();
//	}
//	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE))
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), textureName);
//		textures.emplace_back(aiTextureType_DIFFUSE, pathEntry + textureName.C_Str());
//		textureName.Clear();
//	}
//	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_SPECULAR) > 0)
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), textureName);
//		textures.emplace_back(aiTextureType_SPECULAR, pathEntry + textureName.C_Str());
//		textureName.Clear();
//	}
//	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_AMBIENT) > 0)
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_AMBIENT, 0), textureName);
//		textures.emplace_back(aiTextureType_AMBIENT, pathEntry + textureName.C_Str());
//		textureName.Clear();
//	}
//	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_HEIGHT) > 0)
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_HEIGHT, 0), textureName);
//		textures.emplace_back(aiTextureType_HEIGHT, pathEntry + textureName.C_Str());
//		textureName.Clear();
//	}
//	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_NORMALS) > 0)
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), textureName);
//		textures.emplace_back(aiTextureType_NORMALS, pathEntry + textureName.C_Str());
//		textureName.Clear();
//	}
//	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_NONE) > 0)
//	{
//		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_NONE, 0), textureName);
//		textures.emplace_back(aiTextureType_NONE, pathEntry + textureName.C_Str());
//		textureName.Clear();
//	}
//}
//
//void Mesh::InitDrawable(Graphics& gfx, const Technique& tech, std::string name, uint32_t id)
//{
//	db.SetName(derivedNodeName);
//	db.SetID(id);
//	InitBuffers(gfx);
//	db.AppendTechnique(tech);
//}
//
//void Mesh::Submit(size_t channel)
//{
//	db.Submit(channel);
//}
//
//void Mesh::LinkTechnique(RenderGraph& rg)
//{
//	db.LinkTechnique(rg);
//}
//
//void Mesh::SetName(std::string name)
//{
//	derivedNodeName = name;
//}
//
//std::string Mesh::GetName() const
//{
//	return derivedNodeName;
//}
//
//void Mesh::InitBuffers(Graphics& gfx)
//{
//	db.indexBuffer = std::make_unique<IndexBuff>(gfx, indices);
//	db.vertexBuffer = std::make_unique<VertexBuffer>(gfx, m_vertices);
//	db.primitiveTopology = std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//}