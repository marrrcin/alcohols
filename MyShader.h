#pragma once
#include "GL/glew.h"
#include "stdafx.h"

class MyShader 
{
private:
	GLuint shaderProgram; 
	GLuint vertexShader; 
	GLuint geometryShader; 
	GLuint fragmentShader; 
	char* readFile(const char* fileName); 
	GLuint loadShader(GLenum shaderType, const char* fileName); 
public:
	//TODO: Shader files for objects
	MyShader(const char* vertexShaderFile, const char* geometryShaderFile, const char* fragmentShaderFile);
	~MyShader();
	void use(); 
	GLuint getUniformLocation(char* variableName); 
	GLuint getAttribLocation(char* variableName); 
};

