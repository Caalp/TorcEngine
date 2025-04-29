#pragma once
//#include <string>
//#include <vector>
//#include <map>
//#include "additional_headers.h"
//
//class Mesh;
//
//struct KeyFrame
//{
//	void Interpolate(float t, DirectX::XMMATRIX& M);
//	float dt;
//	bool hasPos;
//	bool hasScal;
//	bool hasRot;
//	DirectX::XMFLOAT3 positionKey;
//	DirectX::XMFLOAT4 rotationKey;
//	DirectX::XMFLOAT3 scalingKey;
//};
//struct AnimationClip
//{
//	double duration; //duration in ticks
//	double ticksPerSec;
//	std::map<std::string,std::vector<KeyFrame>> frames;
//};
//class Node
//{
//	friend class AnimatedCharacter;
//	friend class Model;
//public:
//	Node(int id, const std::string& name, std::vector<Mesh*> meshPtrs, const DirectX::XMMATRIX& transform);
//	Node(int id, const std::string& name, std::vector<Mesh*> meshPtrs, const DirectX::XMMATRIX& transform, const DirectX::XMMATRIX& toRoot);
//	void AddChild(std::unique_ptr<Node> pChild);
//
//private:
//	int id;
//	std::string name;
//	DirectX::XMMATRIX transformation;
//	DirectX::XMMATRIX toRootTransform;
//	std::vector<std::unique_ptr<Node>> childPtrs;
//	std::vector<Mesh*> meshPtrs;
//};