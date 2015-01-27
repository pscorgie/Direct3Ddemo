#pragma once
#include "OrthoCamera.h"
#include "Game.h"
#include "GameObject.h"
class MiniMap
{
private:
	ID3D11Device*           _pd3dDevice;
	ID3D11DeviceContext*    _pImmediateContext;
	ID3D11ShaderResourceView*_pSRV;
	ID3D11RenderTargetView*   _pRTV;
	OrthoCamera*			_pOrthoCamera;
	XMFLOAT2				_position;
	XMFLOAT2				_size;
	D3D11_VIEWPORT          _viewPort;
	Game*					_game;

	ID3D11Buffer*           _pVertexBuffer;
	ID3D11Buffer*           _pIndexBuffer;
	GameObject*				_map, *_border;
	MeshData				_billboardMesh;

public:
	MiniMap(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, int width, int height, Game* game);
	~MiniMap();
	void CreateTextureViews(int width, int height);
	void InitCamera();

	void RenderToMap(ConstantBuffer& cb, ID3D11Buffer* _pConstantBuffer, ID3D11BlendState* _pTransparency);
	void Draw(ConstantBuffer& cb, ID3D11Buffer* _pConstantBuffer);
};

