#include "Core/Asset/Node.h"

//Node::Node(int id, const std::string& name, std::vector<Mesh*> meshPtrs, const DirectX::XMMATRIX& transform) :
//	id(id),
//	meshPtrs(std::move(meshPtrs)),
//	name(name)
//{
//	this->transformation = transform;
//
//}
//
//Node::Node(int id, const std::string& name, std::vector<Mesh*> meshPtrs, const DirectX::XMMATRIX& transform, const DirectX::XMMATRIX& toRoot) :
//	id(id),
//	meshPtrs(std::move(meshPtrs)),
//	name(name)
//{
//	this->transformation = transform;
//	this->toRootTransform = toRoot;
//}
//
//
//void Node::AddChild(std::unique_ptr<Node> pChild)
//{
//	childPtrs.push_back(std::move(pChild));
//}