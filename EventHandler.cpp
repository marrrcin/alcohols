#include "stdafx.h"
#include "EventHandler.h"
#include "CollisionDetector.h"
#include <cmath>


EventHandler::EventHandler()
{
	this->cameraSpeed = 0.4f;
	this->cameraYrange = 10.0f;

	this->mouseSpeed = 0.1f;

	this->lastMouseX = 1024>>1;
	this->lastMouseY = 576>>1;

	this->toRad = 3.14159265/180.0;
}


EventHandler::~EventHandler()
{
}

bool EventHandler::CanMoveTo(glm::vec3 newPosition)
{
	glm::vec2 point;
	point.x=newPosition.x;
	point.y=newPosition.z;
	if(CollisionDetector::IsPointOutOfBounds(point))
			return false;

	return true;
}

void EventHandler::SoberUp()
{
	this->cameraSpeed = 0.4f;
	this->cameraYrange = 10.0f;
	this->mouseSpeed = 0.1f;
	this->params->player->soberUp();
}

void EventHandler::KeyDown(unsigned char c, int x, int y)
{
	glm::vec3 center = this->params->center;
	glm::vec3 observer = this->params->observer;
	glm::vec3 nose = this->params->nose;
	

	// utrudnione poruszanie do przodu
	if (c == 'w')
	{
		this->params->player->stepsLeft--;

		//co 50 kroków zmieniaj kierunek zataczania siê
		if (this->params->player->stepsLeft < 0)
		{
			this->params->player->goLeft = !this->params->player->goLeft;
			this->params->player->stepsLeft = 50;
		}

		int randInt = rand() % 200;
		char tab[2];
		tab[0] = 'w';

		//zataczaj siê w lewo
		if (this->params->player->goLeft)
			tab[1] = 'a';
		//zataczaj siê w prawo
		else
			tab[1] = 'd';

		if (randInt < this->params->player->intoxicationLevel)
		{
			int randIndex = rand() % 2;
			c = tab[randIndex];
		}

	}

	// move forward
	if(c=='w')
	{
		this->temp = glm::normalize(glm::vec3(center.x,observer.y,center.z)-observer);
		observer = this->params->observer + this->temp*this->cameraSpeed;
		if(CanMoveTo(observer))
		{
			this->params->observer+=this->temp*this->cameraSpeed;
			this->params->center+=this->temp*this->cameraSpeed;
		}
	}
	//move backwards
	else if(c=='s')
	{
		this->temp = glm::normalize(glm::vec3(center.x,observer.y,center.z)-observer);
		observer = this->params->observer - this->temp*this->cameraSpeed;
		if(CanMoveTo(observer))
		{
			this->params->observer-=this->temp*this->cameraSpeed;
			this->params->center-=this->temp*this->cameraSpeed;
		}
	}
	//move right
	else if(c=='d')
	{
		this->temp = glm::normalize(center-observer);
		this->temp2 = glm::cross(nose,this->temp);

		observer = this->params->observer - this->temp2*this->cameraSpeed;
		if(CanMoveTo(observer))
		{
			this->params->observer-=this->temp2*this->cameraSpeed;
			this->params->center-=this->temp2*this->cameraSpeed;
		}
	}
	//move left
	else if(c=='a')
	{
		this->temp = glm::normalize(center-observer);
		this->temp2 = glm::cross(nose,this->temp);
		observer = this->params->observer + this->temp2*this->cameraSpeed;
		if(CanMoveTo(observer))
		{
			this->params->observer += this->temp2*this->cameraSpeed;
			this->params->center += this->temp2*this->cameraSpeed;
		}
	}
	//interakcja z obiektem
	else if(c==' ')
	{
		this->params->collisionAction = true;
		if(this->cameraSpeed > 0.2)
			this->cameraSpeed = 0.4 - (this->params->player->intoxicationLevel / 1000.0);
		if (this->cameraYrange > 5.0)
			this->cameraYrange = 10.0 - (this->params->player->intoxicationLevel / 40.0);
		if (this->mouseSpeed > 0.05)
			this->mouseSpeed = 0.1 - (this->params->player->intoxicationLevel / 4000.0);
	}

	//print info about alcohol
	else if (c == 'n')
	{
		this->params->printInfo = true;
	}

	//sober up + reset butelek
	else if (c == 'q')
	{
		this->SoberUp();
		std::cout << "Sobered up! Now you can drink some more..." << std::endl;
	}

	//obs³uga przesuwacza obiektów
	else if (c == 'r')
	{
		this->params->currentAction = rotate;
		std::cout << "current action: rotate" << std::endl;
	}
	else if (c == 't')
	{
		this->params->currentAction = translate;
		std::cout << "current action: translate" << std::endl;
	}
	else if (c == 'u')
	{
		this->params->currentAction = scale;
		std::cout << "current action: scale" << std::endl;
	}
	else if (c == 'x')
	{
		this->params->actionAxis = ActionAxis::x;
		if (this->params->currentAction == Action::rotate)
		{
			this->params->modelMover->RotateUpdate(ActionAxis::x);
		}
			
		std::cout << "current axis: x" << std::endl;
	}
	else if (c == 'y')
	{
		this->params->actionAxis = ActionAxis::y;
		if (this->params->currentAction == Action::rotate)
		{
			this->params->modelMover->RotateUpdate(ActionAxis::y);
		}
		std::cout << "current axis: y" << std::endl;
	}
	else if (c == 'z')
	{
		this->params->actionAxis = ActionAxis::z;
		if (this->params->currentAction == Action::rotate)
		{
			this->params->modelMover->RotateUpdate(ActionAxis::z);
		}
			
		std::cout << "current axis: z" << std::endl;
	}
	else if (c == 'm')
	{
		this->params->modelMover->isEnabled = !this->params->modelMover->isEnabled;
		if (this->params->modelMover->isEnabled == true)
			std::cout << "Entered moving mode." << std::endl;
		else
			std::cout << "Quitted moving mode." << std::endl;
	}
	else if (c == 'i') //up
	{
		std::cout << "Increase by: " << std::endl;
		float inc = 1.0;
		std::cin >> inc;
		this->UpdateMover(inc);
	}
	else if (c == 'k') //down
	{
		std::cout << "Decrease by: " << std::endl;
		float dec = 1.0;
		std::cin >> dec;
		this->UpdateMover(-dec);
	}
	//print info about model matrix
	else if (c == 'p')
	{
		this->params->modelMover->Print();
	}

	//koniec obs³ugi przesuwacza
	
	else if(c == 'c')
	{
		//kamera pos debug
		std::cout<<"cam x "<<this->params->observer.x<<", y "<<this->params->observer.y<<", z "<<this->params->observer.z<<std::endl;
		std::cout<<"lookAt x "<<this->params->center.x<<", y "<<this->params->center.y<<", z "<<this->params->center.z<<std::endl;

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

// chodzenie strza³kami
void EventHandler::SpecialKeyDown(int c,int x,int y)
{
	if(c==GLUT_KEY_UP)
		this->KeyDown('w', x, y);
	else if(c==GLUT_KEY_DOWN)
		this->KeyDown('s', x, y);
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


