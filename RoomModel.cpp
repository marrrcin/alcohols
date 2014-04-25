#include "stdafx.h"
#include "RoomModel.h"


RoomModel::RoomModel(void)
{
	this->LoadModelFromObjFile("roomv3.obj");
	this->angle=99;
	this->lastTime=0;
	this->speed=90;

	this->lights.ambient[0]=0.0f;
	this->lights.ambient[1]=0.0f;
	this->lights.ambient[2]=0.0f;
	this->lights.ambient[3]=1.0f;

	this->lights.diffuse[0]=1.0f;
	this->lights.diffuse[1]=1.0f;
	this->lights.diffuse[2]=1.0f;
	this->lights.diffuse[3]=1.0f;

	this->lights.position[0]=6.11f;
	this->lights.position[1]=5.0f;
	this->lights.position[2]=-4.924f;
	this->lights.position[3]=1.0f;//identyfikuje jako spotlight

	this->lights.spotlightAt[0]=1.0f;
	this->lights.spotlightAt[1]=0.0f;
	this->lights.spotlightAt[2]=0;
	this->lights.spotlightAt[3]=1.0f;
}


RoomModel::~RoomModel(void)
{

}

void RoomModel::Draw()
{
	//Obliczenie macierzy rzutowania
	glm::mat4 *P = this->perspectiveMatrix;
	glm::mat4 *V = this->viewMatrix;
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(*P));
	glMatrixMode(GL_MODELVIEW);
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::scale(M,glm::vec3(3.0f));
	M = glm::rotate(M,90.0f,glm::vec3(0.0f,1.0f,0.0f));
	//M = glm::rotate(M,this->angle, glm::vec3(0.0f, 1.0f, 0.0f));
	glLoadMatrixf(glm::value_ptr(*V*M));
	glDisable(GL_COLOR_MATERIAL);
	
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0f,1.0f,1.0f);
	//glEnable(GL_LIGHT3);
	glLightfv(GL_LIGHT3,GL_POSITION,this->lights.position);
	//glLightfv(GL_LIGHT3,GL_AMBIENT,this->lights.ambient);
	glLightfv(GL_LIGHT3,GL_DIFFUSE,this->lights.diffuse);
	/*glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,this->lights.spotlightAt);
	glLightf(GL_LIGHT3,GL_SPOT_EXPONENT,10.0f);
	glLightf(GL_LIGHT3,GL_SPOT_CUTOFF,20.0f);*/
	this->RenderObject();
	
	//glDisable(GL_LIGHT3);
	
}

void RoomModel::NextFrame()
{
	/*int actTime=glutGet(GLUT_ELAPSED_TIME);
	int interval=actTime-this->lastTime;
	lastTime=actTime;
	this->angle+=this->speed*interval/1000.0;
	if (this->angle>360) this->angle-=360;*/
}