#pragma once

#include <directxmath.h>
#include <d3d11.h>

using namespace DirectX;

struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT2 TexC;

	bool operator<(const SimpleVertex other) const
	{
		return memcmp((void*)this, (void*)&other, sizeof(SimpleVertex)) > 0;
	}
};

struct Light
{
	XMFLOAT4 diffuseLight;
	XMFLOAT4 ambientLight;
	XMFLOAT4 specularLight;
	XMFLOAT3 lightVecW;
	float spot;
	XMFLOAT3 position;
	float range;
	XMFLOAT3 att;
	float pad;
};

struct Material
{
	XMFLOAT4 diffuseMaterial;
	XMFLOAT4 ambientMaterial;
	XMFLOAT4 specularMaterial;
};

struct Fog
{
	float fogStart;
	float fogRange;
	float fogOn;
	float pad;
	XMFLOAT4 fogColour;
	
};

struct ConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
	Light light[5];
	
	Material material;
	Fog fog;

	float specularPower;
	XMFLOAT3 eyePosW;
	float blur;
	float map;

};



struct MeshData
{
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
	UINT VBStride;
	UINT VBOffset;
	UINT IndexCount;
};

struct Vector2
{
	int x;
	int y;
};
