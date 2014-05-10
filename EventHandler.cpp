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

	//obs³uga przesuwacza obiektów
	else if (c == 'r')
	{
		this->params->currentAction = rotate;
		std::cout << "current action : rotate" << std::endl;
	}
	else if (c == 't')
	{
		this->params->currentAction = translate;
		std::cout << "current action : translate" << std::endl;
	}
	else if (c == 'u')
	{
		this->params->currentAction = scale;
		std::cout << "current action : scale" << std::endl;
	}
	else if (c == 'x')
	{
		this->params->actionAxis = ActionAxis::x;
		if (this->params->currentAction == Action::rotate)
		{
			this->params->modelMover->RotateUpdate(ActionAxis::x);
		}
			
		std::cout << "current axis : x" << std::endl;
	}
	else if (c == 'y')
	{
		this->params->actionAxis = ActionAxis::y;
		if (this->params->currentAction == Action::rotate)
		{
			this->params->modelMover->RotateUpdate(ActionAxis::y);
		}
		std::cout << "current axis : y" << std::endl;
	}
	else if (c == 'z')
	{
		this->params->actionAxis = ActionAxis::z;
		if (this->params->currentAction == Action::rotate)
		{
			this->params->modelMover->RotateUpdate(ActionAxis::z);
		}
			
		std::cout << "current axis : z" << std::endl;
	}
	else if (c == 'm')
	{
		this->params->modelMover->isEnabled = !this->params->modelMover->isEnabled;
	}
	else if (c == 'i') //up
	{
		this->UpdateMover(0.05);
	}
	else if (c == 'k') //down
	{
		this->UpdateMover(-0.05);
	}
	else if (c == 'p')
	{
		this->params->modelMover->Print();
	}

	//koniec obs³ugi przesuwacza
	
	else if(c=='c')
	{
		//kamera pos debug
		std::cout<<"cam x "<<this->params->observer.x<<", y "<<this->params->observer.y<<", z "<<this->params->observer.z<<std::endl;
		
		//kucanie
		this->params->crouch = !this->params->crouch;
		if (this->params->crouch)
		{
			this->params->observer.y = 3.0f;
		}
		else
		{
			this->params->observer.y = 5.0f;
		}
	}
}

void EventHandler::UpdateMover(float value)
{
	switch (this->params->actionAxis)
	{
		case ActionAxis::x:
		{
			this->params->ax = value;
			break;
		}

		case ActionAxis::y:
		{
			this->params->ay = value;
			break;
		}

		case ActionAxis::z:
		{
			this->params->az = value;
			break;
		}

		default:
			break;
	}
	this->params->modelMover->Update(this->params->currentAction,this->params->actionAxis, this->params->ax, this->params->ay, this->params->az);
	this->params->ax = 0;
	this->params->ay = 0;
	this->params->az = 0;
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


