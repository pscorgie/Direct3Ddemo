#pragma once
#include "Structures.h"
#include "GameObject.h"
#include "Camera.h"
#include "DDSTextureLoader.h"
#include "OBJLoader.h"
#include "Billboard.h"
#include <vector>
#include "ContentLoader.h"
#include "SkyBox.h"
#include "Car.h"

using namespace DirectX;
#define PARTS 6
#define CAMERA 1
#define CAR 2
#define CARIN 3
#define CARBACK 4
#define FIXDOWN 9
#define FIXED 0

class Game
{
private:
	// DX objects
	ID3D11Device*           _pd3dDevice;
	ID3D11DeviceContext*    _pImmediateContext;

	// Game Objects
	XMFLOAT4X4				_world;
	Camera*					_camera;
	std::vector<GameObject*> _objects, _crowds;
	Car*					_car, *_ai;
	bool					_left, _right, _up, _down;
	SkyBox*					_sky;
	int						_cameraView;
	XMFLOAT3				_direction;
	Light					_carLight, _aiLight, _sceneLight, _pointLight1, _pointLight2;
	bool					_night, _blur, _bKey, _nKey;


	void InitGameObjects();
	void Input();
	void MoveCamera(float t);
	void OrientCamera();
	void UpdateLights();

public:
	Game(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);
	~Game();

	void Update(float t);
	void Draw(ConstantBuffer& cb, ID3D11Buffer* _pConstantBuffer, ID3D11BlendState*	_pTransparency, bool map);
	Camera* camera(){ return _camera; }
	void setCamera(Camera* c){ _camera = c; }
	bool isNight(){ return _night; }
	bool isBlur(){ return _blur; }
	Light getCarLight();
	Light getAiLight();
	Light getSceneLight();
	Light getPLight1(){ return _pointLight1; }
	Light getPLight2(){ return _pointLight2; }
};

