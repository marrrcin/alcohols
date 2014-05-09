#include "stdafx.h"
#include "EventHandler.h"
#include <cmath>


EventHandler::EventHandler()
{
	this->cameraSpeed=0.5f;
	this->cameraYrange=15.0f;

	this->mouseSpeed=0.1f;

	this->lastMouseX=1024>>1;
	this->lastMouseY=576>>1;

	this->toRad= 3.14159265/180.0;
}


EventHandler::~EventHandler()
{
}

void EventHandler::KeyDown(unsigned char c, int x, int y)
{
	glm::vec3 center = this->params->center;
	glm::vec3 observer = this->params->observer;
	glm::vec3 nose = this->params->nose;
	
	if(c=='w')
	{
		this->temp = glm::normalize(glm::vec3(center.x,observer.y,center.z)-observer);
		this->params->observer+=this->temp*this->cameraSpeed;
		this->params->center+=this->temp*this->cameraSpeed;
	}
	else if(c=='s')
	{
		this->temp = glm::normalize(glm::vec3(center.x,observer.y,center.z)-observer);
		this->params->observer-=this->temp*this->cameraSpeed;
		this->params->center-=this->temp*this->cameraSpeed;
	}
	else if(c=='d')
	{
		this->temp = glm::normalize(center-observer);
		this->temp2 = glm::cross(nose,this->temp);
		this->params->observer-=this->temp2*this->cameraSpeed;
		this->params->center-=this->temp2*this->cameraSpeed;
	}
	else if(c=='a')
	{
		this->temp = glm::normalize(center-observer);
		this->temp2 = glm::cross(nose,this->temp);
		this->params->observer+=this->temp2*this->cameraSpeed;
		this->params->center+=this->temp2*this->cameraSpeed;
	}
	else if(c=='c')
	{
		//kamera pos debug
		std::cout<<"cam x "<<this->params->observer.x<<", y "<<this->params->observer.y<<", z "<<this->params->observer.z<<std::endl;
		//this->params->light3on=!this->params->light3on;
		std::cout<<this->params->light3on<<std::endl;
	}
}

void EventHandler::KeyUp(unsigned char c, int x, int y)
{

}

void EventHandler::SpecialKeyDown(int c,int x,int y)
{
	if(c==GLUT_KEY_UP)
		this->KeyDown('w',x,y);
	else if(c==GLUT_KEY_DOWN)
		this->KeyDown('s',x,y);
}

void EventHandler::SpecialKeyUp(int c,int x,int y)
{
	//
}

void EventHandler::MouseMove(int x,int y)
{
	this->difference=this->lastMouseX-x;
	this->lastMouseX=x;
	if(this->difference!=0)
	{
		//poziomo
		glm::mat4 rotation = glm::translate(glm::mat4(1.0f),this->params->observer);
		rotation = glm::rotate(rotation,difference*(this->cameraSpeed),this->params->nose);
		rotation = glm::translate(rotation,-this->params->observer);
		this->params->center=glm::vec3(rotation*glm::vec4(this->params->center,1.0f));
	}

	this->difference=this->lastMouseY-y;
	this->lastMouseY=y;
	if(this->difference!=0)
	{
		//pionowo
		this->params->center.y+=difference;
		if(this->params->center.y>90.0f)
			this->params->center.y=90.0f;
		else if(this->params->center.y<-90.0f)
			this->params->center.y=-90.0f;

	}

	//centrowanie myszki
	if(this->lastMouseX<(1024>>1)-20 || this->lastMouseX>(1024>>1)+20)
	{
		glutWarpPointer(1024>>1,this->lastMouseY);
		this->lastMouseX=1024>>1;
	}

	if(this->lastMouseY<(576>>1)-20 || this->lastMouseY>(576>>1)+20)
	{
		glutWarpPointer(this->lastMouseX,576>>1);
		this->lastMouseY=576>>1;
	}
	
	
}


