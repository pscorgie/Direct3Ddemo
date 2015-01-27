#include "Car.h"


Car::Car(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, bool player) : _player(player)
{
	InitObjects(pd3dDevice, pImmediateContext);
	_left = false; _right = false; _up = false; _down = false;
	_move = 0.0f; _turn = 0.0f; 
	if (_player)
		_speed = 2.7f;
	else
	{
		_speed = 2.5f;
	}
	_point = 0; _lerp = 0;
}


Car::~Car()
{
}
void Car::Update(float t)
{
	if (_player)
	{
		Body()->Move(_move);
		if (_move != 0.0f)
		{
			if (_move <= 0.0f)
				_turn = -_turn;
			Body()->RotateY(_turn);
		}
	}
	else
	{
		MoveAI(t);
	}

	for (size_t i = 0; i < _parts.size(); i++)
	{
		if (_parts[i]->GetName() == "ftyre")
		{
			float move = 0.0f;
			float turn = 0.0f;
			if (_move > 0.0f)
			{
				move = -_move * 300.0 *t;
			}
			else  if (_move < 0.0f)
			{
				move = -_move * 300.0 *t;
			}
			if (_turn != 0.0f)
			{
				turn = _turn * 100;
			}
			_parts[i]->SetRotation(move, turn, 0.0f);
		}
		if (_parts[i]->GetName() == "btyre")
		{
			_parts[i]->SetRotation(-_move * 300.0 *t, 0.0f, 0.0f);
		}
		_parts[i]->UpdateWorld();
	}

	_move = 0.0;
	_turn = 0.0;
}

void Car::MoveAI(float t)
{
	float speed = _speed;
	_move = 0.05 * speed;
	Body()->Move(_move);
	

	XMFLOAT3 pos = Body()->GetPosition();
	XMFLOAT3 point = _trackPoints[_point];
	XMFLOAT3 result = XMFLOAT3(point.x - pos.x, point.y - pos.y, point.z - pos.z);
	XMVECTOR r = XMLoadFloat3(&result);
	r = XMVector3Normalize(r);

	XMVECTOR at = XMLoadFloat3(&Body()->GetAt());
	r = XMVectorLerp(at, r, 0.001 * speed);
	XMStoreFloat3(&result, r);

	Body()->setAt(result);
	if (pos.x - point.x <= 10 && point.x - pos.x <= 10 && pos.z - point.z <= 10 && point.z - pos.z <= 10)
	{
		_point++;
		if (_point >= _trackPoints.size())
			_point = 0;
		_lerp = 0.0;
	}
	if (_lerp < 1)
		_lerp+= 0.0001;

}
void Car::SetPlayer(bool p)
{ 
	_player = p; 
	FindNearest(); 
}
void Car::FindNearest()
{
	float x = Body()->GetPosition().x;
	float z = Body()->GetPosition().z;
	float smallX = 100.0f;
	float smallZ = 100.0f;
	for (size_t i = 0; i < _trackPoints.size(); i++)
	{
		if (Body()->GetPosition().x > _trackPoints[i].x)
		{
			x = Body()->GetPosition().x - _trackPoints[i].x;
			if (x < smallX)
			{
				if (Body()->GetPosition().z > _trackPoints[i].z)
				{
					z = Body()->GetPosition().z - _trackPoints[i].z;
					if (z < smallZ)
					{
						smallX = x;
						smallZ = z;
						_point = i;
					}
				}
				else
				{
					z = _trackPoints[i].z - Body()->GetPosition().z;
					if (z < smallZ)
					{
						smallX = x;
						smallZ = z;
						_point = i;
					}
				}
			}
		}
		else
		{
			x = _trackPoints[i].x - Body()->GetPosition().x;
			if (x < smallX)
			{
				if (Body()->GetPosition().z > _trackPoints[i].z)
				{
					z = Body()->GetPosition().z - _trackPoints[i].z;
					if (z < smallZ)
					{
						smallX = x;
						smallZ = z;
						_point = i;
					}
				}
				else
				{
					z = _trackPoints[i].z - Body()->GetPosition().z;
					if (z < smallZ)
					{
						smallX = x;
						smallZ = z;
						_point = i;
					}
				}
			}
		}
	}
}
void Car::MoveCar()
{
	if (_left) // A
	{
		_turn -= 0.001f * _speed;
	}
	if (_right) // D
	{
		_turn += 0.001f * _speed;
	}
	if (_up) // W
	{
		_move += 0.05f * _speed;
	}
	if (_down) // S
	{
		_move -= 0.05f * _speed;
	}


}
void Car::Draw(ConstantBuffer& cb, ID3D11Buffer* pConstantBuffer, ID3D11BlendState* pTransparency, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
	float blendFactor[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	for (size_t i = 0; i < _parts.size(); i++)
	{
		cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&_parts[i]->GetWorld()));
		pImmediateContext->UpdateSubresource(pConstantBuffer, 0, nullptr, &cb, 0, 0);
		if (i == 5)
			pImmediateContext->OMSetBlendState(pTransparency, blendFactor, 0xffffffff);
		_parts[i]->Draw(pd3dDevice, pImmediateContext);
	}
	pImmediateContext->OMSetBlendState(0, 0, 0xffffffff);
}

void Car::InitObjects(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
	_parts = ContentLoader::LoadCar("car.txt", pd3dDevice, _player);	
	_trackPoints = ContentLoader::LoadPoints("points.txt");
	_trackPoints.erase(_trackPoints.begin());
}

GameObject* Car::Body()
{ 
	if (!_parts.empty())
		return _parts.front();
	else
		return nullptr;
}