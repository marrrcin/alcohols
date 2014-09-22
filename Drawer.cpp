#include "stdafx.h"
#include "Drawer.h"
#include "ModelMover.h"
#include "ModelFactory.h"


Drawer::Drawer(EventParameters *params)
{
	ModelFactory modelFactory;
	modelFactory.CreateObjectsToDraw(&(this->objectsToDraw));

	std::cout << "\t> Objects created! Activating collidable objects..." << std::endl;

	modelFactory.GetObjectsForCollisionsCheck(&(this->objectsToDraw), &(this->collidableObjects));
	this->params = params;

	std::cout << "\t> Assigning model mover..." << std::endl;
	this->AssignModelMover();

	std::cout << "\t> Creating new player..." << std::endl;
	this->player = new Player();
}


Drawer::~Drawer()
{
	delete this->objectsToDraw["vodka"]->modelMover;

	for(auto it = this->collidableObjects.begin(); it!=this->collidableObjects.end(); ++it)
	{
		delete (*it).second; 
	}

	for (auto it = this->objectsToDraw.begin(); it != this->objectsToDraw.end(); ++it)
	{
		delete (*it).second;
	}

}

void Drawer::AssignModelMover()
{
		auto mover = new ModelMover();
		this->objectsToDraw["vodka"]->modelMover = mover;
		this->params->modelMover = mover;

}

void Drawer::Display()
{

	//Wyczyszczenie okna
	glClearColor(172.0/255,213.0/255,1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Obliczenie macierzy rzutowania
	//kat widzenia , stosunek wymiarow okna,plaszczyzna odcinania bliska, daleka, 
	glm::mat4 P = glm::perspective(this->params->perspectiveAngle, 16.0f/9.0f, 1.0f, 150.0f);

	//Obliczenie macierzy widoku (de facto ustawienie kamery na scenie);
	glm::mat4 V = glm::lookAt(
		this->params->observer, //pozycja kamery
		this->params->center, //"CO JA PACZE"
		this->params->nose);
	this->PassMatrixesToAllObjects(&V, &P);

	//Za³adowanie macierzy rzutowania do OpenGL
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));

	//Przygotowanie do ³adowania macierzy widoku i modelu
	glMatrixMode(GL_MODELVIEW);

	
	if(this->params->light3on)
		glEnable(GL_LIGHT3);
	else
		glDisable(GL_LIGHT3);


	this->objectsToDraw["room"]->Draw();
	for (auto i = this->objectsToDraw.begin(); i != this->objectsToDraw.end(); i++)
	{
		if (i->first != "room" && i->first != "glass")
		{
			i->second->Draw();
		}
	}

	auto M = glm::mat4(1.0f);
	auto x = this->params->center.x;
	auto y = this->params->center.y;
	auto z = this->params->center.z;
	M = glm::translate(M, glm::vec3(x, y, z));

	glEnable(GL_COLOR_MATERIAL);
	glColor3d(1, 0, 0);
	glLoadMatrixf(glm::value_ptr(V * M));
	// czerwone cos
	glutSolidSphere(1.0f, 10, 10);
	glDisable(GL_COLOR_MATERIAL);
	
	//na koncu szyby
	this->objectsToDraw["glass"]->Draw();

	//kolizje v1
	this->HandleCollisions();

	//Przerzucenie tylnego bufora na przedni
	glutSwapBuffers();

	
}


void Drawer::HandleCollisions()
{
	Model *modelWithCollision;
	CollisionStatus *status;
	bool collision = false;;

	for(auto i = this->collidableObjects.begin(); i != this->collidableObjects.end(); i++)
	{
																										// kat kolizji, promien
		CollisionDetector::CheckForCollisions(i->first->modelMatrix, this->params->observer, this->params->center, 15, 3, i->second);
		if (*(i->second) == CollisionStatus::detected)
		{
			modelWithCollision = i->first;
			status = i->second;
			modelWithCollision->collisionDetected = true;
			collision = true;
			break;								//tylko jedna kolizja w danym momencie
		}
		else
			i->first->collisionDetected = false;

	}

	if(collision)
	{

		//printing info about alcohol
		if (this->params->printInfo)
			modelWithCollision->printInfo();

		this->params->printInfo = false;

		//changing collision status
		if (this->params->collisionAction == true)
		{
			std::cout << "Starting collision action! " << std::endl;

			this->player->drinkAlcohol(modelWithCollision->alcohol);

			this->params->collisionAction = false;
			/*
			if (*(modelWithCollision->collisionStatus) != CollisionStatus::handling)
			{
				*status = CollisionStatus::handling;
				modelWithCollision->collisionStatus = status;
			}
			*/
		}
	}

}

void Drawer::PrepareNextFrame()
{
	for (auto i = this->objectsToDraw.begin(); i != this->objectsToDraw.end(); i++)
	{
		i->second->NextFrame();
	}
	glutPostRedisplay();
}

void Drawer::PassMatrixesToAllObjects(glm::mat4 *viewMatrix, glm::mat4 *pMatrix)
{
	for (auto it = this->objectsToDraw.begin(); it != this->objectsToDraw.end(); ++it)
	{
		it->second->SetMatrixes(viewMatrix, pMatrix);
	}
}