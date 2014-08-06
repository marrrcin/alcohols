#include "stdafx.h"
#include "Drawer.h"
#include "ModelMover.h"
#include "ModelFactory.h"

Drawer::Drawer(EventParameters *params)
{
	ModelFactory modelFactory;
	modelFactory.CreateObjectsToDraw(&(this->objectsToDraw));
	modelFactory.GetObjectsForCollisionsCheck(&(this->objectsToDraw),&(this->collidableObjects));
	this->params=params;
	this->AssignModelMover();
}


Drawer::~Drawer()
{
	delete this->objectsToDraw["beerCan"]->modelMover;

	for(auto it = this->collidableObjects.begin();it!=this->collidableObjects.end();++it)
	{
		delete (*it).second; // co tak naprawdê jest usuwane?
	}

	for (auto it = this->objectsToDraw.begin(); it != this->objectsToDraw.end(); ++it)
	{
		delete (*it).second;
	}
}

void Drawer::AssignModelMover()
{
		auto mover = new ModelMover();
		this->objectsToDraw["beerCan"]->modelMover=mover;
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

	//Obliczenie macierzy widoku (de fact ustawienie kamery na scenie);
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
	
	
	
	//glLightfv(GL_LIGHT3,GL_AMBIENT,ambientColor);
	
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
	/*this->objectsToDraw["beerBottle"]->Draw();
	this->objectsToDraw["closet1"]->Draw();
	this->objectsToDraw["table"]->Draw();
	this->objectsToDraw["barrel"]->Draw();
	this->objectsToDraw["mug"]->Draw();
*/
	auto M = glm::mat4(1.0f);
	auto x = this->params->center.x;
	auto y = this->params->center.y;
	auto z = this->params->center.z;
	M = glm::translate(M,glm::vec3(x,y,z));
	glEnable(GL_COLOR_MATERIAL);
	glColor3d(1,0,0);
	glLoadMatrixf(glm::value_ptr(V*M));
	glutSolidSphere(1.0f,10,10);
	glDisable(GL_COLOR_MATERIAL);
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
	bool collisionDetected = false;
	for(auto i = this->collidableObjects.begin(); i!=this->collidableObjects.end(); i++)
	{
																											// kat kolizji, promien
		CollisionDetector::CheckForCollisions(i->first->modelMatrix,this->params->observer,this->params->center,15,3,i->second);
		if(*(i->second)==CollisionStatus::detected)
		{
			std::cout<<"Collision!"<<std::endl;
			modelWithCollision = i->first;
			status = i->second;
			collisionDetected = true;
			break;								//tylko jedna kolizja w danym momencie
		}
	}

	if(collisionDetected && this->params->collisionAction==true)
	{
		this->params->collisionAction=false;
		if(*(modelWithCollision->collisionStatus)!=CollisionStatus::handling)
		{
			*status=CollisionStatus::handling;
			modelWithCollision->collisionStatus=status;
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

void Drawer::PassMatrixesToAllObjects(glm::mat4 *viewMatrix,glm::mat4 *pMatrix)
{
	for (auto it = this->objectsToDraw.begin(); it != this->objectsToDraw.end(); ++it)
	{
		it->second->SetMatrixes(viewMatrix, pMatrix);
	}
}