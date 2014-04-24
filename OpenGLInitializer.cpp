#include "stdafx.h"
#include "OpenGLInitializer.h"

OpenGLInitializer::OpenGLInitializer()
{
}


OpenGLInitializer::~OpenGLInitializer()
{
}

bool OpenGLInitializer::Initialize(int screenWidth, int screenHeight,std::string title, int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	

	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(title.c_str());
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	return true;
}

void OpenGLInitializer::SetDrawer(Drawer *drawer)
{
	this->drawer = drawer;
	this->drawer->CreateObjectsToDraw();
	self = this;
	glutDisplayFunc(OpenGLInitializer::DisplayFunction);
	glutIdleFunc(OpenGLInitializer::IdleFunction);
}

void OpenGLInitializer::SetEventHandler(EventHandler *eventHandler)
{
	this->events = eventHandler;
	glewInit();
	
	//obsluga klawiatury
	glutKeyboardFunc(OpenGLInitializer::KeyDownEventHandler);
	glutKeyboardUpFunc(OpenGLInitializer::KeyUpEventHandler);
	glutSpecialFunc(OpenGLInitializer::SpecialKeyDownEventHandler);
	glutSpecialUpFunc(OpenGLInitializer::SpecialKeyUpEventHandler);

	//myszka
	glutPassiveMotionFunc(OpenGLInitializer::MouseMove);
}

void OpenGLInitializer::StartMainLoop()
{
	glutMainLoop();
}

