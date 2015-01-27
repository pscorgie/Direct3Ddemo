#pragma once
#include "GameObject.h"
#include "OBJLoader.h"
#include "DDSTextureLoader.h"
#include <vector>
#include "ContentLoader.h"

#define PARTS 6

using namespace DirectX;

class Car
{
private:
	std::vector<GameObject*>	_parts;
	std::vector<XMFLOAT3>		_trackPoints;
	bool						_player, _left, _right, _up, _down;
	float						_move, _speed, _turn, _lerp;
	int							_point;
	XMFLOAT3					_prevAt;

	void MoveAI(float t);
	void FindNearest();
public:
	Car(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, bool player);
	~Car();
	void Update(float t);
	void Draw(ConstantBuffer& cb, ID3D11Buffer* _pConstantBuffer, ID3D11BlendState* _pTransparency, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	void InitObjects(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	GameObject* Body();
	void MoveCar();
	void Input(bool l, bool r, bool u, bool d){_left = l; _right = r; _up = u; _down = d;}
	void SetPlayer(bool p);
};

