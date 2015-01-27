#include "ContentLoader.h"


std::vector<GameObject*> ContentLoader::Load(std::string filename, ID3D11Device* _pd3dDevice)
{
	std::string line;
	std::ifstream infile;
	std::vector < GameObject* > objects;
	infile.open(filename);
	ID3D11ShaderResourceView* treeTex = nullptr;
	CreateDDSTextureFromFile(_pd3dDevice, L"Pine_tree.dds", nullptr, &treeTex);
	MeshData billboardMesh = OBJLoader::Load("board.obj", _pd3dDevice);
	
	if (infile.is_open())
	{
		while (!infile.eof()) // To get you all the lines.
		{
			infile >> line;

			if (line.compare("o") == 0)
			{
				infile >> line;
				if (line.compare("tree") == 0)
				{
					// create billboard object
		
					
					GameObject* tree = new Billboard();
					tree->Initialise(billboardMesh, treeTex);
					tree->SetName("tree");
					objects.push_back(tree);
				}
				if (line.compare("track") == 0)
				{

					ID3D11ShaderResourceView* trackTex = nullptr;
					CreateDDSTextureFromFile(_pd3dDevice, L"track.dds", nullptr, &trackTex);
					MeshData trackMesh = OBJLoader::Load("plane.obj", _pd3dDevice);
					GameObject* track = new GameObject();
					track->Initialise(trackMesh, trackTex);
					track->SetName("track");
					objects.push_back(track);
				}

				if (line.compare("finish") == 0)
				{

					ID3D11ShaderResourceView* banner = nullptr;
					CreateDDSTextureFromFile(_pd3dDevice, L"banner.dds", nullptr, &banner);
					GameObject* ban = new GameObject();
					ban->Initialise(billboardMesh, banner);
					ban->SetName("finish");
					objects.push_back(ban);
				}

				if (line.compare("lamp") == 0)
				{

					ID3D11ShaderResourceView* lamp = nullptr;
					CreateDDSTextureFromFile(_pd3dDevice, L"bleacher.dds", nullptr, &lamp);
					MeshData lmesh = OBJLoader::Load("lamp.obj", _pd3dDevice);
					GameObject* track = new GameObject();
					track->Initialise(lmesh, lamp);
					track->SetName("lamp");
					objects.push_back(track);
				}

			}

			if (line.compare("s") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetScale(x, y, z);
				}
			}
			if (line.compare("t") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetTranslation(x, y, z);
				}
			}
			if (line.compare("p") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetPosition(x, y, z);
				}
			}
			if (line.compare("r") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetRotation(x, y, z);
				}
			}
		}
	}
	infile.close();
	return objects;
}


std::vector<GameObject*> ContentLoader::LoadSky(std::string filename, ID3D11Device* _pd3dDevice)
{
	std::string line;
	std::ifstream infile;
	std::vector < GameObject* > objects;
	infile.open(filename);
	if (infile.is_open())
	{
		while (!infile.eof()) // To get you all the lines.
		{
			infile >> line;

			if (line.compare("o") == 0)
			{
				infile >> line;
				ID3D11ShaderResourceView* skyTex = nullptr;

				if (line.compare("sky1") == 0)
				{
					CreateDDSTextureFromFile(_pd3dDevice, L"skybox5.dds", nullptr, &skyTex);
				}
				if (line.compare("sky2") == 0)
				{
					CreateDDSTextureFromFile(_pd3dDevice, L"skybox1.dds", nullptr, &skyTex);
				}
				if (line.compare("sky3") == 0)
				{
					CreateDDSTextureFromFile(_pd3dDevice, L"skybox4.dds", nullptr, &skyTex);
				}
				if (line.compare("sky4") == 0)
				{
					CreateDDSTextureFromFile(_pd3dDevice, L"skybox3.dds", nullptr, &skyTex);
				}
				if (line.compare("sky5") == 0)
				{
					CreateDDSTextureFromFile(_pd3dDevice, L"skybox2.dds", nullptr, &skyTex);
				}
				if (line.compare("sky6") == 0)
				{
					CreateDDSTextureFromFile(_pd3dDevice, L"skybox6.dds", nullptr, &skyTex);
				}
				MeshData billboardMesh = OBJLoader::Load("board.obj", _pd3dDevice);
				GameObject* sky = new GameObject();
				sky->Initialise(billboardMesh, skyTex);
				objects.push_back(sky);
			}

			if (line.compare("s") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetScale(x, y, z);
				}
			}
			if (line.compare("t") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetTranslation(x, y, z);
				}
			}
			if (line.compare("p") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetPosition(x, y, z);
				}
			}
			if (line.compare("r") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetRotation(x, y, z);
				}
			}
		}
	}
	infile.close();
	return objects;
}

std::vector<XMFLOAT3> ContentLoader::LoadPoints(std::string filename)
{
	std::string line;
	std::ifstream infile;
	std::vector < XMFLOAT3 > objects;
	infile.open(filename);
	if (infile.is_open())
	{
		while (!infile.eof()) // To get you all the lines.
		{
			infile >> line;

			if (line.compare("p") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				XMFLOAT3 p = XMFLOAT3(x, y, z);
				objects.push_back(p);
			}
		}
	}
	infile.close();
	return objects;
}

std::vector<GameObject*> ContentLoader::LoadCar(std::string filename, ID3D11Device* _pd3dDevice, bool player)
{
	std::string line;
	std::ifstream infile;
	std::vector < GameObject* > objects;
	infile.open(filename);
	ID3D11ShaderResourceView* carTex = nullptr;
	if (player)
	{
		CreateDDSTextureFromFile(_pd3dDevice, L"GtaRE.dds", nullptr, &carTex);
	}
	else
	{
		CreateDDSTextureFromFile(_pd3dDevice, L"GtaRE2.dds", nullptr, &carTex);
	}


	if (infile.is_open())
	{
		while (!infile.eof()) // To get you all the lines.
		{
			infile >> line;
		
			if (line.compare("o") == 0)
			{
				infile >> line;
				if (line.compare("body") == 0)
				{

					MeshData bodyMesh = OBJLoader::Load("body.obj", _pd3dDevice);
					GameObject* body = new GameObject();
					body->Initialise(bodyMesh, carTex);
					body->SetName("body");
					objects.push_back(body);
				}
				if (line.compare("ftyre") == 0)
				{
					MeshData bodyMesh = OBJLoader::Load("frontTyre.obj", _pd3dDevice);
					GameObject* body = new GameObject();
					body->Initialise(bodyMesh, carTex);
					body->SetName("ftyre");
					objects.push_back(body);
				}
				if (line.compare("btyre") == 0)
				{
					MeshData bodyMesh = OBJLoader::Load("backTyre.obj", _pd3dDevice);
					GameObject* body = new GameObject();
					body->Initialise(bodyMesh, carTex);
					body->SetName("btyre");
					objects.push_back(body);
				}
				if (line.compare("glass") == 0)
				{
					MeshData bodyMesh = OBJLoader::Load("glass.obj", _pd3dDevice);
					GameObject* body = new GameObject();
					body->Initialise(bodyMesh, carTex);
					body->SetName("glass");
					objects.push_back(body);
				}

			}

			if (line.compare("s") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetScale(x, y, z);
				}
			}
			if (line.compare("t") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetTranslation(x, y, z);
				}
			}
			if (line.compare("p") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetPosition(x, y, z);
				}
			}
			if (line.compare("ro") == 0)
			{
				// set scale
				float x;
				infile >> x;
				if (!objects.empty())
				{
					objects.back()->RotateY(x);
				}
			}
			if (line.compare("r") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetRotation(x, y, z);
				}
			}
			if (line.compare("pa") == 0)
			{
				// set scale
				std::string parent;
				infile >> parent;
				if (!objects.empty())
				{
					for (size_t i = 0; i < objects.size(); i++)
					{
						if (parent.compare(objects[i]->GetName()) == 0)
						{
							objects.back()->SetParent(objects[i]);
						}
					}
				}
			}

		}
	}
	infile.close();
	return objects;
}

std::vector<GameObject*> ContentLoader::LoadCrowd(std::string filename, ID3D11Device* _pd3dDevice)
{
	std::string line;
	std::ifstream infile;
	std::vector < GameObject* > objects;
	infile.open(filename);
	ID3D11ShaderResourceView* personTex1 = nullptr;
	CreateDDSTextureFromFile(_pd3dDevice, L"person.dds", nullptr, &personTex1);
	ID3D11ShaderResourceView* personTex2 = nullptr;
	CreateDDSTextureFromFile(_pd3dDevice, L"person2.dds", nullptr, &personTex2);
	ID3D11ShaderResourceView* personTex3 = nullptr;
	CreateDDSTextureFromFile(_pd3dDevice, L"person3.dds", nullptr, &personTex3);
	MeshData billboardMesh = OBJLoader::Load("board.obj", _pd3dDevice);

	if (infile.is_open())
	{
		while (!infile.eof()) // To get you all the lines.
		{
			infile >> line;

			if (line.compare("o") == 0)
			{
				infile >> line;
				if (line.compare("person") == 0)
				{
					// create billboard object
					GameObject* person = new Billboard();
					person->Initialise(billboardMesh, personTex1);
					person->SetName("person");
					objects.push_back(person);
				}
				if (line.compare("person2") == 0)
				{
					// create billboard object
					GameObject* person = new Billboard();
					person->Initialise(billboardMesh, personTex2);
					person->SetName("person");
					objects.push_back(person);
				}
				if (line.compare("person3") == 0)
				{
					// create billboard object
					GameObject* person = new Billboard();
					person->Initialise(billboardMesh, personTex3);
					person->SetName("person");
					objects.push_back(person);
				}
				if (line.compare("bleacher") == 0)
				{

					ID3D11ShaderResourceView* bleacherTex = nullptr;
					CreateDDSTextureFromFile(_pd3dDevice, L"bleacher.dds", nullptr, &bleacherTex);
					MeshData bleacherMesh = OBJLoader::Load("bleachers.obj", _pd3dDevice);
					GameObject* track = new GameObject();
					track->Initialise(bleacherMesh, bleacherTex);
					track->SetName("bleacher");
					objects.push_back(track);
				}

			}

			if (line.compare("s") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetScale(x, y, z);
				}
			}
			if (line.compare("t") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetTranslation(x, y, z);
				}
			}
			if (line.compare("p") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetPosition(x, y, z);
				}
			}
			if (line.compare("r") == 0)
			{
				// set scale
				float x, y, z;
				infile >> x;
				infile >> y;
				infile >> z;
				if (!objects.empty())
				{
					objects.back()->SetRotation(x, y, z);
				}
			}
			if (line.compare("pa") == 0)
			{
				// set scale
				std::string parent;
				infile >> parent;
				if (!objects.empty())
				{
					for (size_t i = 0; i < objects.size(); i++)
					{
						if (parent.compare(objects[i]->GetName()) == 0)
						{
							objects.back()->SetParent(objects[i]);
						}
					}
				}
			}
		}
	}
	infile.close();
	return objects;
}