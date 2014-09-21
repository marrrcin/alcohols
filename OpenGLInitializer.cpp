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
	

	return true;
}

void OpenGLInitializer::SetDrawer(Drawer *drawer)
{
	this->drawer = drawer;
	self = this;
	glutDisplayFunc(OpenGLInitializer::DisplayFunction);
	glutIdleFunc(OpenGLInitializer::IdleFunction);

	//obsluga kolizji
	CollisionDetector::LoadBoundLinesFromFile("roomBounds.txt");
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

//Procedura tworz¹ca bufory VBO zawieraj¹ce dane z tablic opisuj¹cych rysowany obiekt.
void OpenGLInitializer::setupVBO()
{
	for (auto it = this->drawer->objectsToDraw.begin(); it != this->drawer->objectsToDraw.end(); ++it)
	{
		arrayModels[i]->vertexCount = arrayModels[i]->data.vertexCount;

		// Vertices
		glGenBuffers(1, &(arrayModels[i]->bufVertices));
		glBindBuffer(GL_ARRAY_BUFFER, arrayModels[i]->bufVertices);
		glBufferData(GL_ARRAY_BUFFER, arrayModels[i]->data.vertexCount*sizeof(float) * 4, arrayModels[i]->data.vertices, GL_STATIC_DRAW); 

		// Normals
		glGenBuffers(1, &(arrayModels[i]->bufNormals));
		glBindBuffer(GL_ARRAY_BUFFER, arrayModels[i]->bufNormals);
		glBufferData(GL_ARRAY_BUFFER, arrayModels[i]->data.vertexCount*sizeof(float) * 4, arrayModels[i]->data.normals, GL_STATIC_DRAW); 

		// Textures
		glGenBuffers(1, &(arrayModels[i]->bufTexCoords));
		glBindBuffer(GL_ARRAY_BUFFER, arrayModels[i]->bufTexCoords);
		glBufferData(GL_ARRAY_BUFFER, arrayModels[i]->data.vertexCount*sizeof(float) * 2, arrayModels[i]->data.textureCoordinates, GL_STATIC_DRAW); 
	}
}

//Procedura tworz¹ca VAO - "obiekt" OpenGL wi¹¿¹cy numery slotów atrybutów z buforami VBO
void OpenGLInitializer::setupVAO()
{
	for (int i = 0; i<arrayModels.size(); i++)
	{
		GLuint locVertex, locNormal, locTexCoords;

		locVertex = arrayMaterials[arrayModels[i]->materialIndex]->shader->getAttribLocation("vertex");
		locNormal = arrayMaterials[arrayModels[i]->materialIndex]->shader->getAttribLocation("normal");
		locTexCoords = arrayMaterials[arrayModels[i]->materialIndex]->shader->getAttribLocation("texCoords0");

		glGenVertexArrays(1, &(arrayModels[i]->vao));
		glBindVertexArray(arrayModels[i]->vao);

		glBindBuffer(GL_ARRAY_BUFFER, arrayModels[i]->bufVertices);  //Uaktywnij wygenerowany uchwyt VBO 
		glEnableVertexAttribArray(locVertex); //W³¹cz u¿ywanie atrybutu o numerze slotu zapisanym w zmiennej locVertex (atrybut "vertex")
		glVertexAttribPointer(locVertex, 4, GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locVertex maj¹ byæ brane z aktywnego VBO

		glBindBuffer(GL_ARRAY_BUFFER, arrayModels[i]->bufNormals);  //Uaktywnij wygenerowany uchwyt VBO 
		glEnableVertexAttribArray(locNormal); //W³¹cz u¿ywanie atrybutu o numerze slotu zapisanym w zmiennej locNormal (atrybut "normal")
		glVertexAttribPointer(locNormal, 4, GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locNormal maj¹ byæ brane z aktywnego VBO

		glBindBuffer(GL_ARRAY_BUFFER, arrayModels[i]->bufTexCoords);  //Uaktywnij wygenerowany uchwyt VBO 
		glEnableVertexAttribArray(locTexCoords); //W³¹cz u¿ywanie atrybutu o numerze slotu zapisanym w zmiennej locTexCoords (atrybut "normal")
		glVertexAttribPointer(locTexCoords, 2, GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu locNormal maj¹ byæ brane z aktywnego VBO

		glBindVertexArray(0);
	}
}

void OpenGLInitializer::StartMainLoop()
{
	glutMainLoop();
}

