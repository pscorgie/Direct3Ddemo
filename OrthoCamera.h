#pragma once
#include <windows.h>
#include <d3d11.h>
//#include <d3dx11.h>
#include <d3dcompiler.h>
#include <directxmath.h>

using namespace DirectX;

class OrthoCamera
{
private:
	XMFLOAT3 _eye;
	XMFLOAT3 _up;
	XMFLOAT3 _look;
	
	XMFLOAT4X4 _view;
	XMFLOAT4X4 _projection;
public: 
	OrthoCamera();
	~OrthoCamera();
	
	void SetEye(XMFLOAT3 e){ _eye = e; }
	void SetAt(XMFLOAT3 a){ _look = a; }
	void SetUp(XMFLOAT3 u){ _up = u; }
	XMFLOAT3 GetEye(){ return _eye; }
	XMFLOAT4X4 GetView() const { return _view; }
	XMFLOAT4X4 GetProjection() const { return _projection; }

	void UpdateViewMatrix();
	void setLens(float width, float height, float zNear, float zFar);
	void Reset();
};

