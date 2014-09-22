#pragma once
#include "stdafx.h"
#include "ModelMover.h"
#include "CollisionDetector.h"
#include "Alcohol.h"
#include "MyMaterial.h"
#include <thread>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

typedef struct _Face
{
	int x;
	int y;
	int z;
} Face;

// this will be removed?
typedef struct _Light
{
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float position[4];
	float spotlightPos[4];
	float spotlightAt[4];
} Light;

// flat representation of vertces for vao and vbo
typedef struct _flatData
{
	int vertCount;

	float *vert;
	float *tex;
	float *norm;

} FlatData;

class Model
{

private:
	void PrepareFaceString(std::string &line);



protected:
	Light lights;
		
	virtual void RenderObject();

public:
	Model();
	~Model();
	virtual void Draw() = 0;
	virtual void NextFrame() = 0;

	void DrawModel(); // szejdery, tekstury i te sprawy

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

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> textures;
	std::vector<glm::vec3> normals;
	
	glm::mat4 *viewMatrix;
	glm::mat4 *perspectiveMatrix;
	glm::mat4 *modelMatrix;

	//vectors for vao and vbo
	FlatData *flat;
	//initialize flat vectors (for vbo binding)
	void flattenData();

	GLuint vao; // vao handler
	//vbo handlers
	GLuint bufVertices;  
	GLuint bufTextureCoords;
	GLuint bufNormals; 
	GLuint bufIndices;

	int vertexCount;

	CollisionStatus *collisionStatus;
	bool isHandling;
	bool collisionDetected;

	Alcohol *alcohol;
	bool isDrinkable();
	void Model::printInfo();
	bool hasTextures;

	ModelMover *modelMover;

	MyMaterial *material;

};

