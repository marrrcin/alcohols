#pragma once

#include "stdafx.h"


typedef enum _colstat
{
	detected,handling,handled,none
} CollisionStatus;

class CollisionDetector
{
private:

	static const double degreesToRad;

	static double maxX;
	static double maxY;

	static std::vector<glm::vec2> boundLines; //kazda para (czyli jeden vec2), to wspolczynniki funkcji liniowej wyznaczajacej jedna ze scian pokoju
	static std::vector<glm::vec2> boundPoints;

	static double Eval(glm::vec2 p, double a, double b)
	{
		return a*p.x-p.y+b; //(Ax+By+C), przy czym B jest rowne -1, bo wyznaczamy funkcje liniowa y=ax+b, wtedy 0=ax+b-y, stad wspolczynnik przy y jest rowny -1
	}

	static bool IsPointInTriangle(glm::vec2 p1,glm::vec2 p2,glm::vec2 p3,glm::vec2 point)
	{

		//na podstawie http://www.math.us.edu.pl/pgladki/faq/node105.html

		bool isInTriangle = false;

		double a1,b1,a2,b2,a3,b3;
		GetLineFunction(p1,p2,&a1,&b1);
		GetLineFunction(p1,p3,&a2,&b2);
		GetLineFunction(p2,p3,&a3,&b3);

		
		if(Eval(point,a1,b1) * Eval(p3,a1,b1)>0 )
		if(Eval(point,a2,b2) * Eval(p2,a2,b2)>0 )
		if(Eval(point,a3,b3) * Eval(p1,a3,b3)>0 ) //ta, mogl byc to &&, ale tak jest czytelniej
			isInTriangle=true;
		
		return isInTriangle;
	};

	static bool AreSegmentsIntersecting(glm::vec2 seg1a,glm::vec2 seg1b,double a1,double b1,glm::vec2 seg2a,glm::vec2 seg2b,double a2,double b2)
	{
		//odcinki sie przecinaja wtedy, gdy oba przecinaja prosta wyznaczona przez punkty drugiego
		//odcinek przecina prosta, gdy jego konce leza po przeciwnych stronach prostej
		//1. pierwszy odcinek i druga prosta
		if(Eval(seg1a,a2,b2)*Eval(seg1b,a2,b2)<0)
		if(Eval(seg2a,a1,b1)*Eval(seg2b,a1,b1)<0) //2. drugi odcinek i pierwsza prosta
			return true;

		return false;
		
	}

	static short DetermineQuadrant(glm::vec2 point)
	{
		if(point.x>=0 && point.y>=0)
			return 1;
		else if(point.x<0 && point.y>0)
			return 2;
		else if(point.x<0 && point.y<0)
			return 3;
		else
			return 4;
		
	}

	static double CorrectAngleToQuadrant(double angle,short quadrant)
	{
		if(quadrant==1)
			return angle;
		else if(quadrant==2)
			return 180.0*degreesToRad+angle;
		else if(quadrant==3)
			return 180.0*degreesToRad+angle;
		else
			return 360.0*degreesToRad+angle;
	}

public:
	CollisionDetector(void);
	~CollisionDetector(void);

	

	static void LoadBoundLinesFromFile(std::string fileName)
	{
		std::ifstream file(fileName.c_str(), std::ios::in);
		double x,y;
		bool loadedFirstRow = false;
		boundPoints.clear();

		do
		{
			file >> x >> y;
			if(!loadedFirstRow)
			{
				loadedFirstRow=true;
				maxX = x;
				maxY = y;
			}
			else
			{
				if(x>maxX)
					maxX=x;

				if(y>maxY)
					maxY=y;
			}

			if (file.eof())
				break;

			boundPoints.push_back(glm::vec2(x+0.0001,y+0.0001));
		}while(!file.eof());

		//dla kazdej pary trzeba wyzmaczyc funkcje liniowa
		double a,b;
		boundLines.clear();
		for(unsigned i=0;i<boundPoints.size();i++)
		{
			if(i==boundPoints.size()-1) //trzeba polaczyc ostatni z pierwszym
				GetLineFunction(boundPoints[i],boundPoints[0],&a,&b);
			else
				GetLineFunction(boundPoints[i],boundPoints[i+1],&a,&b);

			boundLines.push_back(glm::vec2(a,b));
		}
	}

	static bool IsPointOutOfBounds(glm::vec2 point)
	{
		//sprawdzanie, czy punkt jest wewnatrz pokoju (jezeli odcinek z niego poprowdzaony przecina krawedzie scian nieparzysta ilosc razy, to jest)
		//na podstawie http://www.algorytm.org/geometria-obliczeniowa/przynaleznosc-punktu-do-wielokata.html
		//tworzymy odcinek rownolegly do OX, ktory dlugosc wystarczajaca zeby przeciac dowolna sciane
		glm::vec2 segmentOX1,segmentOX2;
		segmentOX1 = point;
		segmentOX2.x = maxX+100;
		segmentOX2.y = point.y;



		//wspolczynniki kierunkowe prostych dla odcinkow OX
		double ax,bx;
		ax = 0;
		bx = point.y;

		int intersections = 0;
		for(unsigned i=0;i<boundPoints.size();i++)
		{
			if(i!=boundPoints.size()-1)
			{
				if(AreSegmentsIntersecting(segmentOX1,segmentOX2,ax,bx,boundPoints[i],boundPoints[i+1],boundLines[i].x,boundLines[i].y))
					++intersections;
			}
			else
			{
				if(AreSegmentsIntersecting(segmentOX1,segmentOX2,ax,bx,boundPoints[i],boundPoints[0],boundLines[i].x,boundLines[i].y))
					++intersections;		
			}
			
		}

		return (intersections%2==0);

	}

	static void GetLineFunction(glm::vec2 p1,glm::vec2 p2,double *a, double *b)
	{
		//wyznaczanie wspolczynnikow prostej z ukladu rownan metoda wyznacznikow
		double W = p1.x-p2.x;
		double Wa = p1.y-p2.y;
		double Wb = p1.x*p2.y - p2.x*p1.y;

		*a = Wa/W;
		*b = Wb/W;
	};

	static void CheckForCollisions(glm::mat4 *modelMatrix,glm::vec3 &camera,glm::vec3 &lookAt,double angle,double radius,CollisionStatus *status)
	{
		glm::vec2 p1,p2,p3,tmp; //punkty trojkata
		p1.x=camera.x;
		p1.y=camera.z;

		
		tmp.x = lookAt.x-camera.x;
		tmp.y = lookAt.z-camera.z;
		double directionAngle = atan(tmp.y/tmp.x); //ustawienie, jakby camera byla srodkiem ukladu wpolrzednych
		directionAngle = CorrectAngleToQuadrant(directionAngle,DetermineQuadrant(tmp));


		angle = angle*degreesToRad;

		double r = 1.5*radius;


		//przesuniecie wektora bazowego o kat +angle i -angle
		p2.x = r * cos(directionAngle+angle)+camera.x;
		p2.y = r * sin(directionAngle+angle)+camera.z;

		p3.x = r * cos(directionAngle-angle)+camera.x;
		p3.y = r * sin(directionAngle-angle)+camera.z;

		glm::vec2 centerOfModel;
		centerOfModel.x = (*modelMatrix)[3][0];
		centerOfModel.y = (*modelMatrix)[3][2];
		

		if(IsPointInTriangle(p1,p2,p3,centerOfModel))
		{
			if(*status!=CollisionStatus::handling)
			{
				*status=CollisionStatus::detected;
			}
				
		}
		else
		{
			if(*status!=CollisionStatus::handling)
			{
				*status=CollisionStatus::none;
			}
		}
			

	
	};
};


