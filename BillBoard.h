#pragma once
#include "GameObject.h"
class Billboard : public GameObject
{
public:
	Billboard();
	~Billboard();
	void FacePosition(XMFLOAT3 pos);
	
};

