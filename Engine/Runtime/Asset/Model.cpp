#include "Model.h"
//#include "MatHelper.h"
//#include <fstream>
//
//#pragma comment(lib,"Assimp/x86/assimp-vc140-mt.lib")
//
//Model::Model(Graphics& gfx, const std::string& filePath, unsigned int flags)
//{
//	std::string fullpath = std::string(MODEL_PATH) + filePath;
//	std::filesystem::path fp(fullpath);
//	std::string parentPath = fp.parent_path().string() + "/";
//	Assimp::Importer importer;
//	const aiScene* pScene = importer.ReadFile(fullpath, flags);
//	// check if loading fails 
//	// might return 0 or scene data might be incomplete or might not have root node
//	if (pScene == nullptr || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || pScene->mRootNode == nullptr)
//	{
//		return;
//	}
//	uint32_t boneIndex = 0;
//	pMesh.resize(pScene->mNumMeshes);
//	//for (size_t i = 0; i < pScene->mNumMeshes; i++)
//	//{
//	//	uint32_t prevVertexCount = pMesh.m_vertices.size();
//	//	uint32_t prevIndexCount = pMesh.indices.size();
//	for (size_t i = 0; i < pScene->mNumMeshes; i++)
//	{
//		//uint32_t prevVertexCount = pMesh[i].m_vertices.size();
//		//uint32_t prevIndexCount = pMesh[i].indices.size();
//		pMesh[i].ParseMesh(*pScene->mMeshes[i], pScene->mMaterials, parentPath);
//		//vAlignmentInfo[i].m_indexCount = pMesh[i].indices.size() - prevIndexCount;
//		//vAlignmentInfo[i].m_vertexCount = pMesh[i].m_vertices.size() - prevVertexCount;
//		//vAlignmentInfo[i].m_vertexBaseIndex = prevVertexCount;
//		//vAlignmentInfo[i].m_startIndex = prevIndexCount;
//		LoadBones(i, boneIndex, *(pScene->mMeshes[i]));
//	}
//	if (pScene->HasAnimations())
//	{
//		//anims.resize(pScene->mNumAnimations);
//		for (uint32_t animIndex = 0; animIndex < pScene->mNumAnimations; animIndex++)
//		{
//			std::string animName = pScene->mAnimations[animIndex]->mName.data;
//			if (animName == "")
//			{
//				animName = "defaultAnim_" + std::to_string(animIndex);
//			}
//			anims[animName].duration = pScene->mAnimations[animIndex]->mDuration;
//			anims[animName].ticksPerSec = (pScene->mAnimations[animIndex]->mTicksPerSecond != 0.0) ? pScene->mAnimations[animIndex]->mTicksPerSecond : 30.0;
//			////Get number of channels. Each channel corresponds to a mesh (rotation, position node name etc)
//			//anims[animName].frames.resize(pScene->mAnimations[animIndex]->mNumChannels);
//			for (uint32_t channelIndex = 0; channelIndex < pScene->mAnimations[animIndex]->mNumChannels; channelIndex++)
//			{
//				std::string nodeName = pScene->mAnimations[animIndex]->mChannels[channelIndex]->mNodeName.data;
//				//anims[animName].frames[channelIndex].nodeName = pScene->mAnimations[animIndex]->mChannels[channelIndex]->mNodeName.data;
//				// Get position keys for corresponding channel
//				auto mSkeys = pScene->mAnimations[animIndex]->mChannels[channelIndex]->mNumScalingKeys;
//				auto mPkeys = pScene->mAnimations[animIndex]->mChannels[channelIndex]->mNumPositionKeys;
//				auto mRKeys = pScene->mAnimations[animIndex]->mChannels[channelIndex]->mNumRotationKeys;
//				unsigned int m = max(mSkeys, mPkeys);
//				m = max(m, mRKeys);
//				anims[animName].frames[nodeName].resize(m);
//				for (uint32_t i = 0; i < m; i++)
//				{
//					anims[animName].frames[nodeName][i].dt = (float)pScene->mAnimations[animIndex]->mChannels[channelIndex]->mRotationKeys[i].mTime;
//					if (i < mRKeys)
//					{
//						aiQuaternion v = pScene->mAnimations[animIndex]->mChannels[channelIndex]->mRotationKeys[i].mValue;
//						anims[animName].frames[nodeName][i].rotationKey = DirectX::XMFLOAT4(v.x, v.y, v.z, v.w);
//						anims[animName].frames[nodeName][i].hasRot = true;
//					}
//					else
//					{
//						anims[animName].frames[nodeName][i].hasRot = false;
//					}
//					if (i < pScene->mAnimations[animIndex]->mChannels[channelIndex]->mNumPositionKeys)
//					{
//						aiVector3D vPos = pScene->mAnimations[animIndex]->mChannels[channelIndex]->mPositionKeys[i].mValue;
//						anims[animName].frames[nodeName][i].positionKey = DirectX::XMFLOAT3(vPos.x, vPos.y, vPos.z);
//						anims[animName].frames[nodeName][i].hasPos = true;
//					}
//					else
//					{
//						anims[animName].frames[nodeName][i].hasPos = false;
//					}
//					if (i < pScene->mAnimations[animIndex]->mChannels[channelIndex]->mNumScalingKeys)
//					{
//						aiVector3D vScaling = pScene->mAnimations[animIndex]->mChannels[channelIndex]->mScalingKeys[i].mValue;
//						anims[animName].frames[nodeName][i].scalingKey = DirectX::XMFLOAT3(vScaling.x, vScaling.y, vScaling.z);
//						anims[animName].frames[nodeName][i].hasScal = true;
//					}
//					else
//					{
//						anims[animName].frames[nodeName][i].hasScal = false;
//					}
//					/*const DirectX::XMFLOAT3* posKey = reinterpret_cast<const DirectX::XMFLOAT3*>(&v);
//					anims[animName].frames[nodeName][posKeyIndex].positionKey = *posKey;*/
//				}
//			}
//		}
//	}
//	DirectX::XMMATRIX M = DirectX::XMMatrixIdentity();
//	int nextId = 0;
//	pRootNode = ParseNode(nextId, *pScene->mRootNode, M);
//	// Parse bone info from the mesh
//	//boneData.resize(nodes.size());
//	finalTransforms.resize(bones.size());
//}
//
//int Model::GetBoneCount()
//{
//	return bones.size();
//}
//
//void Model::GetFinalTransforms(std::string clipName, float timePos, Node* node, const DirectX::XMMATRIX& parentTransform)
//{
//	auto clip = anims[clipName];
//	int size = clip.frames.size();
//	DirectX::XMMATRIX nodeTransform = node->transformation;
//	DirectX::XMMATRIX appliedTranformation;
//	if (clip.frames.find(node->name) != clip.frames.end())
//	{
//		Interpolate(clipName, node->name, timePos, nodeTransform);
//	}
//	appliedTranformation = nodeTransform * parentTransform;
//	auto nodeId = nodes[node->name]->id;
//
//	// Check if the node is active and has offset matrix
//	if (boneToIndex.find(node->name) != boneToIndex.end())
//	{
//		int boneIndex = boneToIndex[node->name];
//		bones[boneIndex].finalTransform = bones[boneIndex].offsetMatrix * appliedTranformation;
//		finalTransforms[boneIndex] = bones[boneIndex].offsetMatrix * appliedTranformation;
//	}
//	else
//	{
//		node->toRootTransform = appliedTranformation;
//	}
//
//	for (uint32_t i = 0; i < node->childPtrs.size(); i++)
//	{
//		GetFinalTransforms(clipName, timePos, node->childPtrs[i].get(), appliedTranformation);
//	}
//}
//
//bool Model::Interpolate(std::string clipName, std::string nodeName, float timePos, DirectX::XMMATRIX& combinedBoneTransforms)
//{
//	auto animClip = anims[clipName];
//	auto animFrames = animClip.frames;
//	auto frames = animFrames[nodeName];
//	if (timePos <= frames.front().dt)
//	{
//		DirectX::XMVECTOR S = DirectX::XMLoadFloat3(&frames.front().scalingKey);
//		DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&frames.front().positionKey);
//		DirectX::XMVECTOR Q = DirectX::XMQuaternionNormalize(DirectX::XMLoadFloat4(&frames.front().rotationKey));
//		DirectX::XMVECTOR zero = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
//		combinedBoneTransforms = DirectX::XMMatrixAffineTransformation(S, zero, Q, P);
//		return true;
//	}
//	else if (timePos >= frames.back().dt)
//	{
//		DirectX::XMVECTOR S = (frames.back().hasScal == false) ? DirectX::XMLoadFloat3(&frames.front().scalingKey) : DirectX::XMLoadFloat3(&frames.back().scalingKey);
//		DirectX::XMVECTOR P = (frames.back().hasPos == false) ? DirectX::XMLoadFloat3(&frames.front().positionKey) : DirectX::XMLoadFloat3(&frames.back().positionKey);
//		DirectX::XMVECTOR Q = (frames.back().hasRot == false) ? DirectX::XMQuaternionNormalize(DirectX::XMLoadFloat4(&frames.front().rotationKey)) : DirectX::XMQuaternionNormalize(DirectX::XMLoadFloat4(&frames.back().rotationKey));
//		DirectX::XMVECTOR zero = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
//		combinedBoneTransforms = DirectX::XMMatrixAffineTransformation(S, zero, Q, P);
//		return true;
//	}
//	else
//	{
//		DirectX::XMVECTOR S;
//		DirectX::XMVECTOR P;
//		DirectX::XMVECTOR Q;
//		for (uint32_t i = 0; i < frames.size() - 1; i++)
//		{
//			if (timePos >= frames[i].dt && timePos < frames[i + 1].dt)
//			{
//				float lerpPercent = (timePos - frames[i].dt) / (frames[i + 1].dt - frames[i].dt);
//				if (frames[i].hasScal && frames[i + 1].hasScal)
//				{
//					DirectX::XMVECTOR s0 = DirectX::XMLoadFloat3(&frames[i].scalingKey);
//					DirectX::XMVECTOR s1 = DirectX::XMLoadFloat3(&frames[i + 1].scalingKey);
//					S = DirectX::XMVectorLerp(s0, s1, lerpPercent);
//				}
//				else
//				{
//					S = DirectX::XMLoadFloat3(&frames[0].scalingKey);
//				}
//				if (frames[i].hasPos && frames[i + 1].hasPos)
//				{
//					DirectX::XMVECTOR p0 = DirectX::XMLoadFloat3(&frames[i].positionKey);
//					DirectX::XMVECTOR p1 = DirectX::XMLoadFloat3(&frames[i + 1].positionKey);
//					P = DirectX::XMVectorLerp(p0, p1, lerpPercent);
//				}
//				else
//				{
//					P = DirectX::XMLoadFloat3(&frames[0].positionKey);
//				}
//				if (frames[i].hasScal && frames[i + 1].hasRot)
//				{
//					DirectX::XMVECTOR q0 = DirectX::XMLoadFloat4(&frames[i].rotationKey);
//					DirectX::XMVECTOR q1 = DirectX::XMLoadFloat4(&frames[i + 1].rotationKey);
//					Q = DirectX::XMQuaternionNormalize(DirectX::XMQuaternionSlerp(q0, q1, lerpPercent));
//				}
//				else
//				{
//					Q = DirectX::XMLoadFloat4(&frames[i].rotationKey);
//				}
//				//DirectX::XMVECTOR S = (animClip.numScalingKeys == 1) ? DirectX::XMLoadFloat3(&frames.front().scalingKey) : 
//				DirectX::XMVECTOR zero = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
//				combinedBoneTransforms = DirectX::XMMatrixAffineTransformation(S, zero, Q, P);
//				return true;
//			}
//		}
//	}
//	return false;
//}
//
//const std::unique_ptr<Node>& Model::GetRootNode()
//{
//	return pRootNode;
//}
//
//std::map<int, BoneData> Model::GetBones() const
//{
//	return bones;
//}
//
//void Model::LoadBones(uint32_t meshIndex, uint32_t& boneIndex, const aiMesh& mesh)
//{
//	for (uint32_t j = 0; j < mesh.mNumBones; j++)
//	{
//		auto bone = mesh.mBones[j];
//		BoneData boneData;
//		boneData.offsetMatrix = DirectX::XMMatrixTranspose(DirectX::XMMATRIX(&bone->mOffsetMatrix.a1));
//		if (boneToIndex.find(bone->mName.C_Str()) == boneToIndex.end())
//		{
//			bones[boneIndex] = boneData;
//			boneToIndex[bone->mName.C_Str()] = boneIndex++;
//			//boneHierarchy[bone->mName.C_Str()] = boneData;
//		}
//		for (uint32_t weightIndex = 0; weightIndex < bone->mNumWeights; weightIndex++)
//		{
//			uint32_t targetIndex = bone->mWeights[weightIndex].mVertexId;
//			if (pMesh[meshIndex].m_vertices[targetIndex].weights.x == 0.0f)
//			{
//				pMesh[meshIndex].m_vertices[targetIndex].weights.x = bone->mWeights[weightIndex].mWeight;
//				pMesh[meshIndex].m_vertices[targetIndex].boneIndices[0] = boneToIndex[bone->mName.C_Str()];
//
//			}
//			else if (pMesh[meshIndex].m_vertices[targetIndex].weights.y == 0.0f)
//			{
//				pMesh[meshIndex].m_vertices[targetIndex].weights.y = bone->mWeights[weightIndex].mWeight;
//				pMesh[meshIndex].m_vertices[targetIndex].boneIndices[1] = boneToIndex[bone->mName.C_Str()];
//			}
//			else if (pMesh[meshIndex].m_vertices[targetIndex].weights.z == 0.0f)
//			{
//				pMesh[meshIndex].m_vertices[targetIndex].weights.z = bone->mWeights[weightIndex].mWeight;
//				pMesh[meshIndex].m_vertices[targetIndex].boneIndices[2] = boneToIndex[bone->mName.C_Str()];
//			}
//			else if (pMesh[meshIndex].m_vertices[targetIndex].weights.w == 0.0f)
//			{
//				pMesh[meshIndex].m_vertices[targetIndex].weights.w = bone->mWeights[weightIndex].mWeight;
//				pMesh[meshIndex].m_vertices[targetIndex].boneIndices[3] = boneToIndex[bone->mName.C_Str()];
//			}
//		}
//	}
//}
//
//std::unique_ptr<Node> Model::ParseNode(int& nextId, const aiNode& node, const DirectX::XMMATRIX& parentTransform)
//{
//	const auto transformation = DirectX::XMMatrixTranspose(DirectX::XMMATRIX(&node.mTransformation.a1));
//	const auto toNodeToRoot = transformation * parentTransform;
//	std::vector<Mesh*> curMeshPtrs;
//	curMeshPtrs.reserve(node.mNumMeshes);
//	for (size_t i = 0; i < node.mNumMeshes; i++)
//	{
//		const auto meshIdx = node.mMeshes[i];
//		pMesh.at(meshIdx).SetName(node.mName.C_Str());
//		curMeshPtrs.push_back(&pMesh.at(meshIdx));
//	}
//	auto pNode = std::make_unique<Node>(nextId, node.mName.C_Str(), std::move(curMeshPtrs), transformation, toNodeToRoot);
//	std::string nodeName(node.mName.C_Str());
//	if (nodeName != "" && nodes.find(nodeName) == nodes.end())
//	{
//		nodes[nodeName] = pNode.get();
//		nextId++;
//	}
//	for (size_t i = 0; i < node.mNumChildren; i++)
//	{
//		std::string childName = (*node.mChildren[i]).mName.C_Str();
//		if (childName != "")
//		{
//			pNode->AddChild(ParseNode(nextId, *node.mChildren[i], toNodeToRoot));
//		}
//	}
//	return pNode;
//}