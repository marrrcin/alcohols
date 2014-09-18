#include "MyMaterial.h"

MyMaterial::MyMaterial(char* diffusePath, char* specularPath, char* vertextureHandlerShaderPath, char* geometryShaderPath, char* fragmentShaderPath)
{
	diffuseMap = readTexture(diffusePath);
	specularMap = readTexture(specularPath);

	shader = new MyShader(vertextureHandlerShaderPath, geometryShaderPath, fragmentShaderPath);
}

MyMaterial::MyMaterial(char* materialPath)
{
	std::string path = materialPath;

	diffuseMap = readTexture((path + "diff.tga").c_str());
	specularMap = readTexture((path + "spec.tga").c_str());

	shader = new MyShader((path + "vshader.txt").c_str(), NULL, (path + "fshader.txt").c_str());
}

MyMaterial::~MyMaterial()
{
	delete shader;
}

GLuint MyMaterial::readTexture(const char* filename)
{
	GLuint textureHandler;
	TGAImg img;
	glActiveTexture(GL_TEXTURE0);
	if (img.Load((char*)filename) == IMG_OK) 
	{
		glGenTextures(1, &textureHandler); 
		glBindTexture(GL_TEXTURE_2D, textureHandler);

		if (img.GetBPP() == 24)
			glTexImage2D(GL_TEXTURE_2D, 0, 3, img.GetWidth(), img.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.GetImg());
		else if (img.GetBPP() == 32)
			glTexImage2D(GL_TEXTURE_2D, 0, 4, img.GetWidth(), img.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.GetImg());
		else
			std::cout << "Cannot handle format of file: " << filename << std::endl;
	}
	else
		std::cout << "Cannot read file: " << filename << std::endl;
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return textureHandler;
}
