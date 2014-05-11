#pragma once
#include "stdafx.h"


typedef enum _Action
{
	rotate, translate, scale
} Action;

typedef enum _ActionAxis
{
	x,y,z
} ActionAxis;

class ModelMover
{
private:
	glm::vec3 vector;
	float translateX, translateY, translateZ;
	float scaleX, scaleY, scaleZ;
	float rotateX, rotateY, rotateZ, rotateAngle;
public:
	ModelMover();
	~ModelMover();

	bool isEnabled;
	

	glm::mat4 Translate(glm::mat4 &M)
	{
		vector = glm::vec3(translateX, translateY, translateZ);
		return glm::translate(M, vector);
	}

	glm::mat4 Rotate(glm::mat4 &M)
	{
		vector = glm::vec3(rotateX, rotateY, rotateZ);
		return glm::rotate(M, rotateAngle, vector);
	}

	glm::mat4 Scale(glm::mat4 &M)
	{
		vector = glm::vec3(scaleX, scaleY, scaleZ);
		return glm::scale(M, vector);
	}

	void Update(Action action,ActionAxis axis, float x, float y, float z)
	{
		switch (action)
		{
			case Action::rotate:
			{
								   this->rotateAngle += 10 * (x + y + z);
				break;
			}
			case Action::scale:
			{
				this->scaleX += x;
				this->scaleY += y;
				this->scaleZ += z;
				break;
			}

			case Action::translate:
			{
				this->translateX += x;
				this->translateY += y;
				this->translateZ += z;
				break;
			}

			default:
				break;
		}
	}

	void RotateUpdate(ActionAxis axis)
	{
		switch (axis)
		{
		case ActionAxis::x:
		{
							  this->rotateX = this->rotateX>=1?0:1;
							  break;
		}

		case ActionAxis::y:
		{
							  this->rotateY = this->rotateY>=1 ? 0 : 1;
							  break;
		}

		case ActionAxis::z:
		{
							  this->rotateZ = this->rotateZ>=1?0:1;
							  break;
		}

		default:
			break;
		}
	}

	void Print()
	{
		std::cout << "Translate: " << this->translateX << " " << this->translateY << " " << this->translateZ << std::endl;
		std::cout << "Rotate: " << this->rotateX << " " << this->rotateY << " " << this->rotateZ << ", angle " << this->rotateAngle << std::endl;
		std::cout << "Scale: " << this->scaleX << " " << this->scaleY << " " << this->scaleZ << std::endl;
	}
};

