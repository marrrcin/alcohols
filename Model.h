#pragma once
#include "stdafx.h"
#include "ModelMover.h"
#include "CollisionDetector.h"
#include "Alcohol.h"

//JAK TO U¯YC? Patrz Example1.h

//te structy poni¿ej to "na potem" do materia³ów i oœwietlenia
typedef struct _Material
{
	float ambient[3];
	float diffuse[3];
	float specular[3];
	float shiness;
	float dissolve;
	float opticalDensity;
} Material;

typedef struct _Lights
{
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float position[4];
	float spotlightPos[4];
	float spotlightAt[4];
} Lights;

class Model
{
private:
	void PrepareFaceString(std::string &line);



protected:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> textures;
	std::vector<GLushort> elements;

	Material material;
	Lights lights;
		
	


	virtual void RenderObject();
public:
	Model();
	~Model();
	virtual void Draw() = 0;
	virtual void NextFrame() = 0;


	virtual void LoadDefaultPerspectiveMatrix();
	virtual void LoadModelFromObjFile(std::string fileName);
	virtual void LoadMaterialFromMtlFile(std::string fileName);
	virtual void SetMatrixes(glm::mat4 *viewMatrix, glm::mat4 *perspectiveMatrix);
	virtual void ExportLoadedMatrixesToFile(std::string fileName);
	virtual void QuickLoadFromFiles(std::string baseFileName);
	
	static void LoadVectorFromFile(std::string fileName, std::vector<glm::vec3> *vector)
	{
		std::fstream file;
		int size, i;
		float x, y, z;
		file.open(fileName.c_str(), std::fstream::in);
		file >> size;
		for (i = 0; i < size; i++)
		{
			file >> x >> y >> z;
			glm::vec3 vec3;
			vec3.x = x;
			vec3.y = y;
			vec3.z = z;
			(*vector).push_back(vec3);
		}
		file.close();
	}


	glm::mat4 *viewMatrix;
	glm::mat4 *perspectiveMatrix;
	glm::mat4 *modelMatrix;

	CollisionStatus *collisionStatus;
	bool isHandling;

	Alcohol *alcohol;
	bool isDrinkable();

	ModelMover *modelMover;
};

