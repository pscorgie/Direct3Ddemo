#pragma once

#include <windows.h>
#include <Windowsx.h>
#include <iostream> 
#include <d3d11_1.h>
#include <d3dcompiler.h>
//#include <directxmath.h>
#include <directxcolors.h>
#include "resource.h"
#include "Structures.h"
#include "GameObject.h"
#include "Camera.h"
#include "DDSTextureLoader.h"
#include "OBJLoader.h"
#include "Billboard.h"
#include "Game.h"
#include "MiniMap.h"


using namespace DirectX;

#define PARTS 6


class Application
{
private:
	HINSTANCE               _hInst;
	HWND                    _hWnd;
	D3D_DRIVER_TYPE         _driverType;
	D3D_FEATURE_LEVEL       _featureLevel;
	ID3D11Device*           _pd3dDevice;
	ID3D11DeviceContext*    _pImmediateContext;
	IDXGISwapChain*         _pSwapChain;
	ID3D11RenderTargetView* _pRenderTargetView;
	ID3D11VertexShader*     _pVertexShader;
	ID3D11PixelShader*      _pPixelShader;
	ID3D11InputLayout*      _pVertexLayout;
	ID3D11BlendState*		_pTransparency;
	ID3D11Buffer*           _pConstantBuffer;
	ID3D11RasterizerState*	_wireFrame, *_solidFrame;
	D3D11_VIEWPORT			vp;
	bool					_frameState, _tabKeyDown;
	XMFLOAT3				_lightDir;
	XMFLOAT4				_diffuse, _ambient;
	Game*					_game;
	Material				_material;
	Fog						_fog;
	MiniMap* 				_miniMap;
	OrthoCamera*			_test;
	bool					_fogOn, _fKey;
	XMFLOAT3				_direction;

	int						_cameraView;
	Vector2					mLastMousePos;

	ID3D11DepthStencilView* _depthStencilView;
	ID3D11Texture2D*		_depthStencilBuffer;
	ID3D11SamplerState*		_pSamplerLinear;

private:
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitDevice();
	void Cleanup();
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT InitShadersAndInputLayout();

	UINT _WindowHeight;
	UINT _WindowWidth;

public:
	Application();
	~Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	void Update();
	void Draw();
	void OnMouseMove(WPARAM btnState, int x, int y);
	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	bool HandleKeyboard(MSG msg);
	bool HandleMouse(MSG msg);
	void InitGameObjects();
	void InitScene();
};

