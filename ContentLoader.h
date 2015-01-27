#pragma once
#include "Structures.h"
#include "GameObject.h"
#include "Camera.h"
#include "DDSTextureLoader.h"
#include "OBJLoader.h"
#include "Billboard.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>


namespace ContentLoader
{
	std::vector<GameObject*> Load(std::string filename, ID3D11Device* _pd3dDevice);
	std::vector<GameObject*> LoadSky(std::string filename, ID3D11Device* _pd3dDevice);
	std::vector<XMFLOAT3> LoadPoints(std::string filename);
	std::vector<GameObject*> LoadCar(std::string filename, ID3D11Device* _pd3dDevice, bool player);
	std::vector<GameObject*> LoadCrowd(std::string filename, ID3D11Device* _pd3dDevice);
};

