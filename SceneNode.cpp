#include "SceneNode.h"


SceneNode::SceneNode(SceneNode* Parent, GameObject* Object) : _parent(Parent), object(Object), name(NULL)
{
}
SceneNode::~SceneNode()
{}

void SceneNode::SetParentNode(SceneNode* newParent)
{
	_parent->removeChild(this);
	_parent = newParent;
}

void SceneNode::AddChild(SceneNode* child)
{
	child->SetParentNode(this);
	children.push_back(child);

	// if(NULL != child)
	//		if(NULL != child->GetParent())
	//			child->setParent(this)
	//		children.push_back(child);
}
void SceneNode::removeChild(SceneNode* child)
{
	if (NULL != child && !children.empty())
	{
		for (size_t i = 0; i < children.size(); i++)
		{
			if (children[i] == child)
			{
				children.erase(children.begin() + i);
				break;
			}

		}
	}
}

void SceneNode::UpdateWorld(XMMATRIX& parentWorld, float dt)
{
	/*XMMATRIX world;

	for (size_t i = 0; i < children.size(); i++)
	{
	children[i]->UpdateWorld(parentWorld * MovePlanets(dt), dt);
	}
	if (_parent == NULL)
	parentWorld *= MovePlanets(dt);
	object->SetWorld(parentWorld);*/
	for (size_t i = 0; i < this->children.size(); i++)
	{
		this->children[i]->UpdateWorld(parentWorld, dt);
	}
	//if (_parent == NULL)
	parentWorld *= MovePlanets(dt);
	object->SetWorld(parentWorld);
}

XMMATRIX SceneNode::MovePlanets(float dt)
{
	XMMATRIX planet1 = XMMatrixScaling(0.5f, 0.5f, 0.5f) * XMMatrixRotationY(dt) * XMMatrixTranslation(5.0f, 2.0f, 0.0f) * XMMatrixRotationY(dt); // rotate (spin), translate, orbit
	XMMATRIX planet2 = XMMatrixScaling(0.5f, 0.5f, 0.5f) * XMMatrixRotationY(2 * dt) * XMMatrixTranslation(8.0f, 2.0f, 0.0f) * XMMatrixRotationY(0.8*dt);
	
	//if (strcmp(name, "planet2"))
	//	return	XMMatrixScaling(0.5f, 0.5f, 0.5f) * XMMatrixRotationY(dt) * XMMatrixTranslation(5.0f, 2.0f, 0.0f) * XMMatrixRotationY(dt); // rotate (spin), translate, orbit
	//else if (strcmp(name, "planet3"))
	//	return	XMMatrixScaling(0.5f, 0.5f, 0.5f) * XMMatrixRotationY(dt) * XMMatrixTranslation(5.0f, 2.0f, 0.0f) * XMMatrixRotationY(3*dt);
	//	//return XMMatrixScaling(0.5f, 0.5f, 0.5f) * XMMatrixRotationY(2 * dt) * XMMatrixTranslation(8.0f, 2.0f, 0.0f) * XMMatrixRotationY(0.8*dt);
	//else if (strcmp(name, "planet4"))
	//	return XMMatrixScaling(0.2f, 0.2f, 0.2f) * (XMMatrixRotationY(dt) * XMMatrixTranslation(2.0f, 0.0f, 0.0f) * XMMatrixRotationY(5 * dt)) * planet1;
	//else if (strcmp(name, "planet5"))
	//	return XMMatrixScaling(0.2f, 0.2f, 0.2f) * (XMMatrixRotationX(dt) * XMMatrixTranslation(0.0f, 2.0f, 0.0f) * XMMatrixRotationX(5 * dt)) * planet1;
	//else
		return XMMatrixRotationY(0.8*dt);
}
