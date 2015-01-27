#include "BillBoard.h"


Billboard::Billboard() : GameObject()
{
}


Billboard::~Billboard()
{
}

void Billboard::FacePosition(XMFLOAT3 pos)
{
	// Calculate the lookAt vector by the difference between points "at" and position
	XMFLOAT3 Look = XMFLOAT3(pos.x - _position.x, pos.y - _position.y, pos.z - _position.z);
	XMVECTOR L = XMLoadFloat3(&Look);
	L = XMVector3Normalize(L);

	// Calculate the Right vector 
	XMFLOAT3 Up = { 0.0f, 1.0f, 0.0f };
	XMVECTOR U = XMLoadFloat3(&Up);

	XMFLOAT3 Right = { 0.0f, 0.0f, 0.0f };
	XMVECTOR R = XMVector3Cross(L, U);
	R = XMVector3Normalize(R);

	XMStoreFloat3(&Look, L);
	XMStoreFloat3(&Right, R);

	_world(0, 0) = Right.x;
	_world(1, 0) = 0.0f; 
	_world(2, 0) = Right.z;
	_world(3, 0) = _position.x;

	_world(0, 1) = Up.x;
	_world(1, 1) = Up.y;
	_world(2, 1) = Up.z;
	_world(3, 1) = _position.y;

	_world(0, 2) = Look.x;
	_world(1, 2) = 0.0f;
	_world(2, 2) = Look.z;
	_world(3, 2) = _position.z;

	_world(0, 3) = 0.0f;
	_world(1, 3) = 0.0f;
	_world(2, 3) = 0.0f;
	_world(3, 3) = 1.0f;

}