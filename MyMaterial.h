#pragma once

#include "MyShader.h"
#include "GL/glew.h"
#include "glm/gtc/type_ptr.hpp"
#include "Tga.h"

class MyMaterial
{
public:
	GLuint diffuseMap;
	GLuint specularMap;
	MyShader *shader;

	MyMaterial();
	MyMaterial(char* diffusePath, char* specularPath, char* vertexShaderPath, char* geometryShaderPath, char* fragmentShaderPath);
	MyMaterial(char* materialPath);
	~MyMaterial();

private:
	GLuint readTexture(const char* filename);
};