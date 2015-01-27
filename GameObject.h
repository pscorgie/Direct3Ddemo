#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include "Structures.h"

using namespace DirectX;


class GameObject
{
protected:
	MeshData _meshData;
	ID3D11ShaderResourceView * _pTextureRV;
	GameObject* _parent;
	char* _name;

	XMFLOAT3 _position;
	XMFLOAT3 _up;
	XMFLOAT3 _right;
	XMFLOAT3 _look;

	XMFLOAT4X4 _world;

	XMFLOAT4X4 _scale;
	XMFLOAT4X4 _rotate;
	XMFLOAT4X4 _translate;

public:
	GameObject();
	~GameObject();

	virtual void FacePosition(XMFLOAT3 pos){};
	//XMFLOAT4X4 GetWorld() const { return _world; }
	XMFLOAT4X4 GetWorld();

	void UpdateWorld();
	void SetWorld(XMMATRIX& transform);

	void SetName(char* name){ _name = name; }
	char* GetName(){ return _name; }

	void SetScale(float x, float y, float z);
	void SetScale(XMFLOAT4X4 t) { _scale = t; }
	void SetRotation(float x, float y, float z);
	void SetTranslation(float x, float y, float z);
	void SetTranslation(XMFLOAT4X4 t) { _translate = t; }
	XMFLOAT4X4 GetTranslation(){ return _translate; }
	void SetParent(GameObject* g){ _parent = g; }
	GameObject* GetParent(){ return _parent; }

	void SetPosition(float x, float y, float z){ _position.x = x, _position.y = y, _position.z = z; }
	void SetPosition(XMFLOAT3 pos){ _position = pos; }
	XMFLOAT3 GetPosition() const { return _position; }
	XMFLOAT3 GetAt() const{ return _look; }
	void setAt(XMFLOAT3 a){ _look = a; }
	XMFLOAT3 GetUp() const{ return _up; }
	XMFLOAT3 GetRight() const{ return _right; }
	void Move(float d);
	void RotateY(float r);
	void RotateX(float x);
	
	void Initialise(MeshData meshData, ID3D11ShaderResourceView * _pTextureRV);
	virtual void Update(float elapsedTime);
	void Draw(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
};

