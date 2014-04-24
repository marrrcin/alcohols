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
	this->tmpDifference=0;

	this->toRad= 3.14159265/180.0;
}


EventHandler::~EventHandler()
{
}

void EventHandler::KeyDown(unsigned char c, int x, int y)
{
	float tangent = abs(tan(toRad*this->params->cameraRotation));
	float diff=0;
	if(c=='w')
	{
		diff=this->params->cameraZ+this->cameraSpeed;
		this->params->cameraZ+=this->cameraSpeed;

		//this->params->lookAtZ+=this->cameraSpeed;
		if(this->params->cameraRotation<0)
		{
			this->params->cameraX+=this->cameraSpeed * tangent;
			//this->params->lookAtX-=this->cameraSpeed * tangent;
		}
			
		else
		{
			this->params->cameraX-=this->cameraSpeed * tangent;
			//this->params->lookAtX+=this->cameraSpeed * tangent;
		}
	}
	else if(c=='s')
	{
		this->params->cameraZ-=this->cameraSpeed;
		//this->params->lookAtZ-=this->cameraSpeed;
		if(this->params->cameraRotation<0)
		{
			this->params->cameraX-=this->cameraSpeed * tangent;
			//this->params->lookAtX+=this->cameraSpeed * tangent;
		}
			
		else
		{
			this->params->cameraX+=this->cameraSpeed * tangent;
			//this->params->lookAtX-=this->cameraSpeed * tangent;
		}

			
		//this->params->cameraX+=this->cameraSpeed * -this->CalculateLookAtAngle();
	}
	else if(c=='q')
	{
		this->params->cameraRotation-=2.0f;
		if(this->params->cameraRotation<-360.0f)
			this->params->cameraRotation=0.0f;
		//this->CalculateLookAtAngle();

	}
	else if(c=='e')
	{
		this->params->cameraRotation+=2.0f;
		if(this->params->cameraRotation>360.0f)
			this->params->cameraRotation=0.0f;
		//this->CalculateLookAtAngle();
	}

	printf("[%f]camX %f , camZ %f | lookX %f , lookZ %f\n",this->params->cameraRotation,this->params->cameraX,this->params->cameraZ,this->params->lookAtX,this->params->lookAtZ);
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
	printf("[%d,%d]\n",x,y);

	if(!doneY)
	{
		this->tmpDifference=this->lastMouseY-y;
	
		if(this->tmpDifference>0)
		{
			if(this->params->lookAtY<this->cameraYrange)
				this->params->lookAtY+=this->mouseSpeed;
		}
		else
		{
			if(this->params->lookAtY>-this->cameraYrange)
				this->params->lookAtY-=this->mouseSpeed;
		}
		doneY=true;
	}
	else
	{
		this->tmpDifference=this->lastMouseX-x;
		if(this->tmpDifference>0)
		{
			this->params->lookAtX+=2*this->mouseSpeed;
		}
		else
		{
			this->params->lookAtX-=2*this->mouseSpeed;
		}
		doneY=false;
	}

	
	

	this->lastMouseY=y;
	this->lastMouseX=x;

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


void EventHandler::CalculateLookAtAngle()
{
	//float lookAtX = this->params->lookAtX;
	//float lookAtZ = this->params->lookAtZ;

	//float camX = this->params->cameraX;
	//float camZ = this->params->cameraZ;


	//float toRad = this->pi /180.0;
	//float sinx = sin(this->params->cameraRotation *toRad);
	//float cosx = cos(this->params->cameraRotation * toRad);
	//float x = (lookAtX*cosx)-(lookAtZ*sinx);
	//float z = (lookAtX*sinx)+(lookAtZ*cosx);

	//this->params->lookAtX=x;
	//this->params->lookAtZ=z;
	//printf("lookAt x=%f , z=%f\n",x,z);
}