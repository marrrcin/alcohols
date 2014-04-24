#pragma once
class Model
{
private:
	void PrepareFaceString(std::string &line);
protected:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textures;
	std::vector<GLushort> elements;

	virtual void RenderObject();
public:
	Model();
	~Model();
	virtual void Draw() = 0;
	virtual void NextFrame() = 0;
	virtual void LoadModelFromObjFile(std::string fileName);
	virtual void SetMatrixes(glm::mat4 *viewMatrix, glm::mat4 *perspectiveMatrix);

	glm::mat4 *viewMatrix;
	glm::mat4 *perspectiveMatrix;
};

