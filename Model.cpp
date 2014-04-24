#include "stdafx.h"
#include "Model.h"


Model::Model()
{
}


Model::~Model()
{
}

void Model::LoadModelFromObjFile(std::string fileName)
{
	std::ifstream file(fileName.c_str(), std::ios::in);
	std::string buffer;
	std::string firstChar;
	std::string helper;
	int t, q;
	int face[3];
	bool hasTextures = false;
	std::istringstream stringStream, helperStream;
	std::vector<glm::vec3> verticesBuffer;
	std::vector<glm::vec3> normalsBuffer;
	std::vector<glm::vec2> texturesBuffer;
	this->vertices.clear();
	this->normals.clear();
	do
	{
		buffer.clear();
		std::getline(file, buffer);
		if (file.eof())
			break;
		firstChar = buffer.substr(0, 2);
		stringStream.clear();
		stringStream.str(buffer.substr(2));
		if (firstChar == "v " || firstChar =="vn")
		{
			glm::vec3 vertex;
			stringStream >> vertex.x;
			stringStream >> vertex.y;
			stringStream >> vertex.z;
			if (firstChar == "v ")
				verticesBuffer.push_back(vertex);
			else
				normalsBuffer.push_back(vertex);
		}
		else if (firstChar == "vt")
		{
			glm::vec2 texture;
			stringStream >> texture.x;
			stringStream >> texture.y;
			texturesBuffer.push_back(texture);
			hasTextures = true;
		}
		else if (firstChar == "f ")
		{
			this->PrepareFaceString(buffer);
			stringStream.clear();
			stringStream.str(buffer.substr(2));

			for (t = 0; t < 3; t++)
			{
				for (q = 0; q < 3; q++)
				{
					std::getline(stringStream, helper, '/');
					helperStream.clear();
					helperStream.str(helper);
					helperStream >> face[q];
					--face[q];
				}

				this->vertices.push_back(verticesBuffer[face[0]]);
				this->normals.push_back(normalsBuffer[face[2]]);

				if (hasTextures)
					this->textures.push_back(texturesBuffer[face[1]]);
			}
			
		}


	} while (!file.eof());

}


void Model::PrepareFaceString(std::string &line)
{
	auto find = line.find("//");
	while (find != std::string::npos)
	{
		line.insert(find + 1, "0");
		find = line.find("//");
	}

	for (int q = 0; q < line.length(); q++)
	{
		if (line[q] == ' ')
			line[q] = '/';
	}
}

void Model::RenderObject()
{
	glEnableClientState(GL_VERTEX_ARRAY);						// Enable vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);						// Enable normal arrays
	glVertexPointer(3, GL_FLOAT, 0, &this->vertices[0]);				// Vertex Pointer to triangle array
	glNormalPointer(GL_FLOAT, 0, &this->normals[0]);						// Normal pointer to normal array
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());		// Draw the triangles
	glDisableClientState(GL_VERTEX_ARRAY);						// Disable vertex arrays
	glDisableClientState(GL_NORMAL_ARRAY);
}

void Model::SetMatrixes(glm::mat4 *viewMatrix, glm::mat4 *perspectiveMatrix)
{
	this->viewMatrix = viewMatrix;
	this->perspectiveMatrix = perspectiveMatrix;
}