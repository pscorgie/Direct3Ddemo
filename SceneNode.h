#pragma once
#include <vector>
#include "GameObject.h"

class SceneNode
{
private:
	SceneNode* _parent;
	GameObject* object;
	std::vector<SceneNode*> children;
	char* name;
public:
	SceneNode(SceneNode* Parent, GameObject* Object);
	~SceneNode();

	SceneNode* GetParent() const { return _parent; }
	void SetParentNode(SceneNode* newParent);
	void setName(char* c){ name = c; }

	void AddChild(SceneNode* child);
	void removeChild(SceneNode* child);

	GameObject* getObject(){ return object; }

	void UpdateWorld(XMMATRIX& parentWorld, float dt);
	XMMATRIX MovePlanets(float dt);

	std::vector<SceneNode*> getChildren() { return children; }

	/*size_t countChildNodes(const bool& RecursiveCount = false);
	SceneNode* getChildNodeByName(const char* name);*/

};

