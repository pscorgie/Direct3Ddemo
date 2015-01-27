#include "SkyBox.h"


SkyBox::SkyBox(ID3D11Device* pd3dDevice)
{
	_objects = ContentLoader::LoadSky("sky.txt", pd3dDevice);
}


SkyBox::~SkyBox()
{
}
void SkyBox::Update(XMFLOAT3 p)
{
	for (size_t i = 0; i < _objects.size(); i++)
	{
		_objects[i]->SetPosition(p);
		_objects[i]->UpdateWorld();
	}
}
void SkyBox::Draw(ConstantBuffer& cb, ID3D11Buffer* _pConstantBuffer, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
	cb.material.diffuseMaterial = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	cb.material.ambientMaterial = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	cb.material.specularMaterial = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);


	for (size_t i = 0; i < _objects.size(); i++)
	{
		cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&_objects[i]->GetWorld()));
		pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);
		_objects[i]->Draw(pd3dDevice, pImmediateContext);
	}

	cb.material.diffuseMaterial = XMFLOAT4(0.8f, 0.8f, 1.0f, 1.0f);
	cb.material.ambientMaterial = XMFLOAT4(0.0f, 0.0f, 0.1f, 1.0f);
	cb.material.specularMaterial = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
}