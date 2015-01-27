#pragma once
#include "GameObject.h"
#include <vector>
#include "ContentLoader.h"

class SkyBox
{
	std::vector<GameObject*> _objects;
public:
	SkyBox(ID3D11Device* pd3dDevice);
	~SkyBox();
	void Update(XMFLOAT3 p);
	void Draw(ConstantBuffer& cb, ID3D11Buffer* _pConstantBuffer, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
};

