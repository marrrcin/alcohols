#include "MyShader.h"

char* MyShader::readFile(const char* fileName) 
{
	int filesize;
	FILE *myFile;
	char* result;

	myFile = fopen(fileName, "r");
	fseek(myFile, 0, SEEK_END);
	filesize = ftell(myFile);
	fseek(myFile, 0, SEEK_SET);
	result = new char[filesize + 1];
	fread(result, 1, filesize, myFile);
	result[filesize] = 0;
	fclose(myFile);

	return result;
}

GLuint MyShader::loadShader(GLenum shaderType, const char* fileName) {

	GLuint shader = glCreateShader(shaderType);
	const GLchar* shaderSource = readFile(fileName);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	delete[] shaderSource;

	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 1) {
		infoLog = new char[infologLength];
		glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
		std::cout << infoLog << std::endl;
		delete[] infoLog;
	}

	return shader;
}

MyShader::MyShader(const char* vertexShaderFile, const char* geometryShaderFile, const char* fragmentShaderFile) {

	std::cout << "> Loading vertex shader..." << std::endl;
	vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderFile);

	if (geometryShaderFile != NULL) {
		std::cout << "> Loading geometry shader..." << std::endl;
		geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryShaderFile);
	}
	else {
		geometryShader = 0;
	}

	std::cout << "> Loading fragment shader..." << std::endl;
	fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderFile);

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	if (geometryShaderFile != NULL) 
		glAttachShader(shaderProgram, geometryShader);
	glLinkProgram(shaderProgram);

	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 1)
	{
		infoLog = new char[infologLength];
		glGetProgramInfoLog(shaderProgram, infologLength, &charsWritten, infoLog);
		std::cout << infoLog << std::endl;
		delete[]infoLog;
	}

	std::cout << "> SHADER PROGRAM CREATED!" << std::endl;
}

MyShader::~MyShader() {

	glDetachShader(shaderProgram, vertexShader);
	if (geometryShader != 0) 
		glDetachShader(shaderProgram, geometryShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);

	if (geometryShader != 0) 
		glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);

	glDeleteProgram(shaderProgram);
}

void MyShader::use() {
	glUseProgram(shaderProgram);
}

GLuint MyShader::getUniformLocation(char* variableName) {
	return glGetUniformLocation(shaderProgram, variableName);
}

GLuint MyShader::getAttribLocation(char* variableName) {
	return glGetAttribLocation(shaderProgram, variableName);
}