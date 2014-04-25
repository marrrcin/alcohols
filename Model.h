#pragma once

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
	std::vector<glm::vec2> textures;
	std::vector<GLushort> elements;

	Material material;
	Lights lights;

	virtual void RenderObject();
public:
	Model();
	~Model();
	virtual void Draw() = 0;
	virtual void NextFrame() = 0;
	virtual void LoadModelFromObjFile(std::string fileName);
	virtual void LoadMaterialFromMtlFile(std::string fileName);
	virtual void SetMatrixes(glm::mat4 *viewMatrix, glm::mat4 *perspectiveMatrix);

	glm::mat4 *viewMatrix;
	glm::mat4 *perspectiveMatrix;
};

