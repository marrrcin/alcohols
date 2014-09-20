#include "Model.h"
#include "Drawer.h"
#include "alcohols.h"

//JAK TO U¯YC? Patrz Example1.h

Model::Model()
{
	this->collisionStatus = new CollisionStatus();
	*(this->collisionStatus) = CollisionStatus::none;

	this->isHandling=false;
	this->collisionDetected = false;
	this->alcohol = nullptr;
}


Model::~Model()
{

}

void Model::DrawModel()
{
	this->material->shader->use();

	glUniformMatrix4fv(this->material->shader->getUniformLocation("P"), 1, false, glm::value_ptr(*this->perspectiveMatrix));
	glUniformMatrix4fv(this->material->shader->getUniformLocation("V"), 1, false, glm::value_ptr(*this->viewMatrix));
	glUniformMatrix4fv(this->material->shader->getUniformLocation("M"), 1, false, glm::value_ptr(*this->modelMatrix));

	glUniform1f(this->material->shader->getUniformLocation("LIGHTS_COUNT"), globalLights->lightCount);

	glUniform4fv(this->material->shader->getUniformLocation("LIGHTS_POSITION"), globalLights->lightCount, globalLights->positions);
	glUniform1fv(this->material->shader->getUniformLocation("LIGHTS_RADIUS"), globalLights->lightCount, globalLights->radius);
	glUniform1fv(this->material->shader->getUniformLocation("LIGHTS_INTENSITY"), globalLights->lightCount, globalLights->intensity);


	//ustawienie tekstur
	glUniform1i(this->material->shader->getUniformLocation("textureMap0"), 0); //zmienna jednorodna textureMap0 reprezentuje jednostkê teksturuj¹c¹ numer 0
	glUniform1i(this->material->shader->getUniformLocation("textureMap1"), 1); //zmienna jednorodna textureMap1 reprezentuje jednostkê teksturuj¹c¹ numer 1
	glActiveTexture(GL_TEXTURE0); //Uaktywnij jednostkê teksturuj¹c¹ numer 0
	glBindTexture(GL_TEXTURE_2D, this->material->diffuseMap); //Zwi¹¿ aktywn¹ jednostkê teksturuj¹c¹ z tekstur¹ o uchwycie zapisanym w tex0
	glActiveTexture(GL_TEXTURE1); //Uaktywnij jednostkê teksturuj¹c¹ numer 1
	glBindTexture(GL_TEXTURE_2D, this->material->specularMap); //Zwi¹¿ aktywn¹ jednostkê teksturuj¹c¹ z tekstur¹ o uchwycie zapisanym w tex1
	glBindVertexArray(this->vao);

	glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);

	glBindVertexArray(0);
}

bool Model::isDrinkable()
{
	if (this->alcohol == nullptr)
		return false;
	else
		return true;
}

void Model::printInfo()
{
	if (this->isDrinkable())
	{
		std::cout << "Excellent choice! " << this->alcohol->volume << "ml, " << this->alcohol->power << "% of alcohol." << std::endl;
	}
}

void Model::LoadModelFromObjFile(std::string fileName)
{
	std::string folderName = "obj/";
	fileName = folderName.append(fileName);

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
	std::vector<glm::vec3> texturesBuffer;
	this->vertices.clear();
	this->normals.clear();
	do
	{
		buffer.clear();
		std::getline(file, buffer);

		if (file.eof())
			break;

		if (buffer.length() < 2)
			buffer = "zzzzz"; // in case line shorter than 2 chars

		firstChar = buffer.substr(0, 2);
		stringStream.clear();
		stringStream.str(buffer.substr(2));

		//szczególnie do tej czêœci poni¿ej
		if (firstChar == "v " || firstChar == "vn")
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
			glm::vec3 texture;
			stringStream >> texture.x;
			stringStream >> texture.y;
			stringStream >> texture.z;
			texturesBuffer.push_back(texture);
			hasTextures = true;
		}
		//still not sure if this one works properly
		//will look closely into that soon 
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
	if (find == std::string::npos)
	{
		int i = 0;
	}
	while (find != std::string::npos)
	{
		line.insert(find + 1, "0");
		find = line.find("//");
	}

	for (unsigned q = 0; q < line.length(); q++)
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

void Model::LoadMaterialFromMtlFile(std::string fileName)
{

}

void Model::ExportLoadedMatrixesToFile(std::string fileName)
{
	std::fstream file;
	std::string fileName2;
	unsigned i;
	std::string folderName = "quickLoad/";

	fileName2 = folderName.append(fileName);
	fileName2.append("Vertices.txt");
		file.open(fileName2.c_str(), std::fstream::out);
	file << this->vertices.size() << std::endl;
	for (i = 0; i < this->vertices.size(); i++)
	{
		file << this->vertices[i].x << " " << this->vertices[i].y << " " << this->vertices[i].z << std::endl;
	}
	file.close();

	fileName2 = folderName.append(fileName);
	fileName2.append("Normals.txt");
	file.open(fileName2.c_str(), std::fstream::out);
	file << this->normals.size() << std::endl;
	for (i = 0; i < this->normals.size(); i++)
	{
		file << this->normals[i].x << " " << this->normals[i].y << " " << this->normals[i].z << std::endl;
	}
	file.close();

	/* we should probably use these later
	fileName2 = folderName.append(fileName);
	fileName2.append("Textures.txt");
	file.open(fileName2.c_str(), std::fstream::out);
	file << this->textures.size() << std::endl;
	for (i = 0; i < this->textures.size(); i++)
	{
		file << this->textures[i].x << " " << this->textures[i].y << " " << this->textures[i].z << std::endl;
	}
	file.close();
	*/
}

void Model::QuickLoadFromFiles(std::string baseFileName)
{
	std::string folderName = "quickLoad/";
	baseFileName = folderName.append(baseFileName);

	std::string fileName = baseFileName;
	fileName.append("Vertices.txt");
	std::thread t1(Model::LoadVectorFromFile, fileName, &this->vertices);

	fileName = baseFileName;
	fileName.append("Normals.txt");
	std::thread t2(Model::LoadVectorFromFile, fileName, &this->normals);
	/*
	fileName = baseFileName;
	fileName.append("Textures.txt");
	std::thread t3(Model::LoadVectorFromFile, fileName, &this->textures);
	*/

	t1.join();
	t2.join();
	//t3.join();
}

void Model::LoadDefaultPerspectiveMatrix()
{
	glm::mat4 *P = this->perspectiveMatrix;
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(*P));
	glMatrixMode(GL_MODELVIEW);
}