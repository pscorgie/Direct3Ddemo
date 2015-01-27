#pragma once

#include <windows.h>
#include <d3d11.h>
//#include <d3dx11.h>
#include <d3dcompiler.h>
#include <directxmath.h>

using namespace DirectX;

class Camera
{
private:
	
	XMFLOAT3 _position;
	XMFLOAT3 _lookAt;
	XMFLOAT3 _right;
	XMFLOAT3 _up;

	FLOAT _windowWidth;
	FLOAT _windowHeight;
	FLOAT _nearDepth;
	FLOAT _farDepth;

	XMFLOAT4X4 _view;
	XMFLOAT4X4 _projection;

public:
	Camera(XMFLOAT3 position, XMFLOAT3 at, XMFLOAT3 up, FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth);
	~Camera();

	void CalculateViewProjection();

	XMFLOAT4X4 GetView() const { return _view; }
	XMFLOAT4X4 GetProjection() const { return _projection; }

	XMFLOAT4X4 GetViewProjection() const;

	XMFLOAT3 GetPosition() const{ return _position; }
	XMFLOAT3 GetAt() const{ return _lookAt; }
	XMFLOAT3 GetUp() const{ return _up; }
	XMFLOAT3 GetRight() const{ return _right; }

	void SetPosition(XMFLOAT3 position){ _position = position; }
	void SetAt(XMFLOAT3 at){ _lookAt = at; }
	void SetUp(XMFLOAT3 up){ _up = up; }
	void SetRight(XMFLOAT3 right){ _right = right; }

	void Reshape(FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth);
	void Pitch(float p);
	void RotateY(float r);
	void Move(float d);
	void Strafe(float d);
	void Reset();
};

