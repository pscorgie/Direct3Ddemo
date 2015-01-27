#include "MiniMap.h"


MiniMap::MiniMap(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, int width, int height, Game* game)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;
	
	width = 400;
	height = 300;

	_viewPort.Width = (FLOAT)width;
	_viewPort.Height = (FLOAT)height;
	_viewPort.MinDepth = 0.0f;
	_viewPort.MaxDepth = 1.0f;
	_viewPort.TopLeftX = 0;
	_viewPort.TopLeftY = 0;

	CreateTextureViews(width, height);// , height);
	InitCamera();

	_position = XMFLOAT2(0.25f, 0.75f);
	_size = XMFLOAT2(0.25f, 0.25f);
	_game = game;


	_billboardMesh = OBJLoader::Load("board.obj", _pd3dDevice);
	_map = new GameObject();
	_map->Initialise(_billboardMesh, _pSRV);
	_map->SetScale(50, 50, 1.0);// width, height, 1.0f);
	_map->SetTranslation(145.0f, 100.0f, -143.0f); //
	_map->SetRotation(XM_PIDIV2, 0.0f, XM_PI);

	ID3D11ShaderResourceView* satnav = nullptr;
	CreateDDSTextureFromFile(_pd3dDevice, L"satnav.dds", nullptr, &satnav);

	_border = new GameObject();
	_border->Initialise(_billboardMesh, satnav);
	_border->SetScale(1.33f, 2.34f, 1.0f);
	_border->SetTranslation(0.1f, -0.83f, -0.0f);
	_border->SetParent(_map);
}


MiniMap::~MiniMap()
{
}
void MiniMap::CreateTextureViews(int width, int height)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//DXGI_FORMAT_D24_UNORM_S8_UINT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	ID3D11Texture2D* tex;
	_pd3dDevice->CreateTexture2D(&textureDesc, nullptr, &tex);

	_pd3dDevice->CreateRenderTargetView(tex, nullptr, &_pRTV);
	_pd3dDevice->CreateShaderResourceView(tex, nullptr, &_pSRV);

	
	//tex->Release();
}
void MiniMap::InitCamera()
{
	_pOrthoCamera = new OrthoCamera();
	_pOrthoCamera->setLens(400.0f, 400.0f, 0.01f, 500.0f);
	_pOrthoCamera->UpdateViewMatrix();
}

void MiniMap::RenderToMap(ConstantBuffer& cb, ID3D11Buffer* _pConstantBuffer, ID3D11BlendState* _pTransparency)
{
	_pImmediateContext->OMSetRenderTargets(1, &_pRTV, nullptr); // check in right place nullptr
	_pImmediateContext->RSSetViewports(1, &_viewPort);

	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // red,green,blue,alpha
	_pImmediateContext->ClearRenderTargetView(_pRTV, ClearColor);

	XMFLOAT3 pos = _game->camera()->GetPosition();
	pos.y = 1.0f;
	XMFLOAT3 at = _game->camera()->GetPosition();
	at.y = -1.0f;
	_pOrthoCamera->SetEye(pos);
	_pOrthoCamera->SetAt(at);
	_pOrthoCamera->UpdateViewMatrix();

	XMMATRIX view = XMLoadFloat4x4(&_pOrthoCamera->GetView());
	XMMATRIX projection = XMLoadFloat4x4(&_pOrthoCamera->GetProjection());
	XMFLOAT3 eyepos = _pOrthoCamera->GetEye();

	cb.mView = XMMatrixTranspose(view);
	cb.mProjection = XMMatrixTranspose(projection);
	cb.eyePosW = eyepos;
	if (_game->isNight())
		cb.material.ambientMaterial = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	else
		cb.material.ambientMaterial = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	cb.map = 1.0f;
	_game->Draw(cb, _pConstantBuffer, _pTransparency, true);
	cb.map = 0.0f;
}
void MiniMap::Draw(ConstantBuffer& cb, ID3D11Buffer* _pConstantBuffer)
{
	_pOrthoCamera->Reset();
	
	XMMATRIX view = XMLoadFloat4x4(&_pOrthoCamera->GetView());
	XMMATRIX projection = XMLoadFloat4x4(&_pOrthoCamera->GetProjection());
	XMFLOAT3 eyepos = _pOrthoCamera->GetEye();

	cb.mView = XMMatrixTranspose(view);
	cb.mProjection = XMMatrixTranspose(projection);
	cb.eyePosW = eyepos;

	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&_border->GetWorld()));
	_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	_border->Draw(_pd3dDevice, _pImmediateContext);

	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&_map->GetWorld()));
	_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	_map->Draw(_pd3dDevice, _pImmediateContext);

}