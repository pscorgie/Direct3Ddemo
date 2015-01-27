#include "Game.h"


Game::Game(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext) 
	: _pd3dDevice(pd3dDevice), _pImmediateContext(pImmediateContext)
{
	InitGameObjects();
	_cameraView = FIXDOWN;// CAMERA;
	_left = false; _right = false; _up = false; _down = false;

	Light light;
	light.ambientLight = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	light.diffuseLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	light.specularLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	light.att = XMFLOAT3(1.0f, 0.0f, 0.0f);
	light.range = 10000.0f;
	light.spot = 10.0f;

	_carLight = light; _aiLight = light;

	_night = false; _blur = false; _bKey = false; _nKey = false;

	_sceneLight.ambientLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_sceneLight.diffuseLight = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	_sceneLight.specularLight = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	_sceneLight.lightVecW = XMFLOAT3(0.57735f, -0.57735f, 0.57735f); //XMFLOAT3(1.0f, 1.0f, 0.0f);
	_sceneLight.position = XMFLOAT3(0.0f, 5.0f, 0.0f);
	_sceneLight.att = XMFLOAT3(0.0f, 0.1f, 0.0f);
	_sceneLight.range = 100.0f;

	light.ambientLight = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	light.diffuseLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	light.specularLight = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	light.att = XMFLOAT3(0.0f, 0.1f, 0.1f);
	light.range = 100.0f;
	light.spot = 10.0f;

	_pointLight1 = light;
	_pointLight1.position = XMFLOAT3(20.0f, 53.3f, 203.3f);
	_pointLight2 = light;
	_pointLight2.position = XMFLOAT3(20.0f, 53.3f, 286.7f);


}


Game::~Game()
{
}
void Game::Input()
{
	if (GetAsyncKeyState(0x41)) // A
	{
		_left = true;
	}
	else
	{
		_left = false;
	}
	if (GetAsyncKeyState(0x44)) // D
	{
		_right = true;
	}
	else
	{
		_right = false;
	}
	if (GetAsyncKeyState(0x57)) // W
	{
		_up = true;
	}
	else
	{
		_up = false;
	}
	if (GetAsyncKeyState(0x53)) // S
	{
		_down = true;
	}
	else
	{
		_down = false;
	}

	if (GetAsyncKeyState(0x31)) // 1
	{
		_cameraView = CAMERA;
	}
	if (GetAsyncKeyState(0x32)) // 2
	{
		_cameraView = CAR;
		_car->SetPlayer(true);
	}
	if (GetAsyncKeyState(0x33)) // 3
	{
		_cameraView = CARIN;
		_car->SetPlayer(true);
	}
	if (GetAsyncKeyState(0x34)) // 4
	{
		_cameraView = CARBACK;
		_car->SetPlayer(true);
	}
	else if (!GetAsyncKeyState(0x34) && _cameraView == CARBACK)
	{
		_cameraView = CARIN;
	}
	if (GetAsyncKeyState(0x30)) // 0
	{
		_cameraView = FIXED;
	}
	if (GetAsyncKeyState(0x39)) // 9
	{
		_cameraView = FIXDOWN;
	}
	if (GetAsyncKeyState(0x4E) && !_nKey) // N
	{
		_night = !_night;
		_nKey = true;
	}
	else if (!GetAsyncKeyState(0x4E) && _nKey) 
	{
		_nKey = false;
	}
	if (GetAsyncKeyState(VK_SPACE)) // SpaceBar
	{
		_car->SetPlayer(false);
	}
	if (GetAsyncKeyState(0x42) && !_bKey) // B
	{
		_blur = !_blur;
		_bKey = true;
	}
	else if (!GetAsyncKeyState(0x42) && _bKey)
	{
		_bKey = false;

	}
}

void Game::MoveCamera(float t)
{
	float speed = 0.1;
	if (_left) // A
	{
		_camera->Strafe(-speed );
	}
	if (_right) // D
	{
		_camera->Strafe(speed );
	}
	if (_up) // W
	{
		_camera->Move(speed );
	}
	if (_down) // S
	{
		_camera->Move(-speed);
	}
	if (_camera->GetPosition().y <= 0.5)
	{
		XMFLOAT3 pos = _camera->GetPosition();
		pos.y = 0.55f;
		_camera->SetPosition(pos);
	}

}
void Game::OrientCamera()
{
	if (_cameraView == CAR)
	{
		XMFLOAT3 p = _car->Body()->GetPosition();
		p.y += 10.00f;

		XMFLOAT3 a = _car->Body()->GetAt();
		XMFLOAT3 r = _car->Body()->GetRight();
		float d = 20;
		p.x = p.x - a.x * d;
		p.z = p.z - a.z * d;

		a.x = a.x;
		a.z = a.z;
		r.x = -r.x;
		r.y = -r.y;
		r.z = -r.z;
		_camera->SetPosition(p);
		_camera->SetAt(a);
		_camera->SetRight(r);
	}
	if (_cameraView == CARIN)
	{
		XMFLOAT3 p = _car->Body()->GetPosition();
		p.y += 4.7f;

		XMFLOAT3 a = _car->Body()->GetAt();
		XMFLOAT3 r = _car->Body()->GetRight();
		float d = 1;
		p.x = p.x - a.x * d;
		p.z = p.z - a.z * d;

		a.x = a.x;
		a.z = a.z;
		r.x = -r.x;
		r.y = -r.y;
		r.z = -r.z;
		_camera->SetPosition(p);
		_camera->SetAt(a);
		_camera->SetRight(r);
	}
	if (_cameraView == CARBACK)
	{
		XMFLOAT3 p = _car->Body()->GetPosition();
		p.y += 4.7f;

		XMFLOAT3 a = _car->Body()->GetAt();
		XMFLOAT3 r = _car->Body()->GetRight();
		float d = 1;
		p.x = p.x - a.x * d;
		p.z = p.z - a.z * d;

		a.x = -a.x;
		a.z = -a.z;
		_camera->SetPosition(p);
		_camera->SetAt(a);
		_camera->SetRight(r);
	}

	if (_cameraView == FIXED)
	{
		XMFLOAT3 p = XMFLOAT3(0.0f, 150.0f, -350.0f);
		XMFLOAT3 a = XMFLOAT3(0.0f, 0.0f, 1.0f);
		XMFLOAT3 u = XMFLOAT3(0.0f, 1.0f, 0.0f);
		
		_camera->SetPosition(p);
		_camera->SetAt(a);
		_camera->SetUp(u);
		_camera->Reset();
	}
	if (_cameraView == FIXDOWN)
	{
		XMFLOAT3 p = XMFLOAT3(0.0f, 450.0f, -70.0f);
		XMFLOAT3 a = XMFLOAT3(0.0f, -1.0f, 0.1f);
		XMFLOAT3 u = XMFLOAT3(0.0f, 1.0f, 0.0f);

		_camera->SetPosition(p);
		_camera->SetAt(a);
		_camera->SetUp(u);
		_camera->Reset();
	}
}
void Game::Update(float t)
{
	
	Input();
	_car->Input(_left, _right, _up, _down);
	switch (_cameraView)
	{
	case CAR:
		_car->MoveCar();
		break;
	case CAMERA:
		MoveCamera(t);
		break;
	case CARIN:
		_car->MoveCar();
		break;
	case CARBACK:
		_car->MoveCar();
		break;
	}
	
	_car->Update(t);
	_ai->Update(t);
	OrientCamera();
	camera()->CalculateViewProjection();

	for (size_t i = 0; i < _objects.size(); i++)
	{
		_objects[i]->FacePosition(_camera->GetPosition());

	}
	_sky->Update(_camera->GetPosition());
	if (_night)
	{
		UpdateLights();
	}

}

void Game::Draw(ConstantBuffer& cb, ID3D11Buffer* _pConstantBuffer, ID3D11BlendState* _pTransparency, bool map)
{
	float blendFactor[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	_pImmediateContext->OMSetBlendState(0, 0, 0xffffffff);

	cb.material.specularMaterial = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	
	// track & trees
	
	for (size_t i = 0; i < _objects.size(); i++)
	{
		cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&_objects[i]->GetWorld()));
		_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);
		_objects[i]->Draw(_pd3dDevice, _pImmediateContext);
	}
	if (!map)
	{
		// draws crowd and skybox (not included in the minimap)
		for (size_t i = 0; i < _crowds.size(); i++)
		{
			cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&_crowds[i]->GetWorld()));
			_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);
			_crowds[i]->Draw(_pd3dDevice, _pImmediateContext);
		}

		_sky->Draw(cb, _pConstantBuffer, _pd3dDevice, _pImmediateContext);
	}

	cb.material.specularMaterial = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	_ai->Draw(cb, _pConstantBuffer, _pTransparency, _pd3dDevice, _pImmediateContext);
	_car->Draw(cb, _pConstantBuffer, _pTransparency, _pd3dDevice, _pImmediateContext);
	
}

void Game::InitGameObjects()
{
	_sky = new SkyBox(_pd3dDevice);
	_objects = ContentLoader::Load("objects.txt", _pd3dDevice);
	_car = new Car(_pd3dDevice, _pImmediateContext, true);
	_ai = new Car(_pd3dDevice, _pImmediateContext, false);
	_crowds = ContentLoader::LoadCrowd("crowd.txt", _pd3dDevice);

}
void Game::UpdateLights()
{
		_carLight.lightVecW = _car->Body()->GetAt();
		_carLight.lightVecW.y = -0.7f;
		_carLight.position.x = _car->Body()->GetPosition().x + (_car->Body()->GetAt().x*10.0f);
		_carLight.position.y = _car->Body()->GetPosition().y + 10.0f;
		_carLight.position.z = _car->Body()->GetPosition().z + (_car->Body()->GetAt().z*10.0f);

		_aiLight.lightVecW = _ai->Body()->GetAt();
		_aiLight.lightVecW.y = -0.7f;
		_aiLight.position.x = _ai->Body()->GetPosition().x + (_ai->Body()->GetAt().x*10.0f);
		_aiLight.position.y = _ai->Body()->GetPosition().y + 10.0f;
		_aiLight.position.z = _ai->Body()->GetPosition().z + (_ai->Body()->GetAt().z*10.0f);

}
Light Game::getCarLight()
{
	if (_night)
	{
		return _carLight;
	}
	else
	{
		Light light;
		return light;
	}
}
Light Game::getAiLight()
{
	if (_night)
	{
		return _aiLight;
	}
	else
	{
		Light light;
		return light;
	}
}
Light Game::getSceneLight()
{
	if (_night)
	{
		_sceneLight.ambientLight = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
		_sceneLight.diffuseLight = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f); 
		_sceneLight.specularLight = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
		_sceneLight.lightVecW = XMFLOAT3(0.57735f, -0.57735f, 0.57735f); 
		_sceneLight.position = XMFLOAT3(0.0f, 5.0f, 0.0f);
		_sceneLight.att = XMFLOAT3(0.0f, 0.1f, 0.0f);
		_sceneLight.range = 100.0f;
		return _sceneLight;
	}
	else
	{
		_sceneLight.ambientLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		_sceneLight.diffuseLight = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
		_sceneLight.specularLight = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
		_sceneLight.lightVecW = XMFLOAT3(0.57735f, -0.57735f, 0.57735f); 
		_sceneLight.position = XMFLOAT3(0.0f, 5.0f, 0.0f);
		_sceneLight.att = XMFLOAT3(0.0f, 0.1f, 0.0f);
		_sceneLight.range = 100.0f;
		return _sceneLight;
	}
}