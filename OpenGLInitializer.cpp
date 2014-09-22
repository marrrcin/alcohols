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
	std::cout << "\t>Setting up VBO for " << this->drawer->objectsToDraw.size() << " objects! " << std::endl;

	for (auto it = this->drawer->objectsToDraw.begin(); it != this->drawer->objectsToDraw.end(); ++it)
	{
		std::cout << "\t\t" << it->first << std::endl;

		//te obiekty bêd¹ renderowane poprzez odpowiednie metody w swoich klasach
		if (it->first == "barrel" || it-> first == "closet")
			continue;


		//quick fix, bo na razie tylko cognac ma materia³ i szejdera
		if (it->first == "cognac")
		{
			// Vertices
			glGenBuffers(1, &(it->second->bufVertices));
			glBindBuffer(GL_ARRAY_BUFFER, it->second->bufVertices);
			glBufferData(GL_ARRAY_BUFFER, it->second->vertices.size() * sizeof(float) * 4, it->second->flat->vert, GL_STATIC_DRAW);

			// Normals
			glGenBuffers(1, &(it->second->bufNormals));
			glBindBuffer(GL_ARRAY_BUFFER, it->second->bufNormals);
			glBufferData(GL_ARRAY_BUFFER, it->second->normals.size() * sizeof(float) * 4, it->second->flat->norm, GL_STATIC_DRAW);

			// Textures
			glGenBuffers(1, &(it->second->bufTextureCoords));
			glBindBuffer(GL_ARRAY_BUFFER, it->second->bufTextureCoords);
			glBufferData(GL_ARRAY_BUFFER, it->second->textures.size() * sizeof(float) * 2, it->second->flat->tex, GL_STATIC_DRAW);
		} 
	}
}

//Procedura tworz¹ca VAO - "obiekt" OpenGL wi¹¿¹cy numery slotów atrybutów z buforami VBO
void OpenGLInitializer::setupVAO()
{
	for (auto it = this->drawer->objectsToDraw.begin(); it != this->drawer->objectsToDraw.end(); ++it)
	{
		//te obiekty bêd¹ renderowane poprzez odpowiednie metody w swoich klasach
		if (it->first == "barrel" || it->first == "closet")
			continue;

		//quick fix, bo na razie tylko cognac ma materia³ i szejdera
		if (it->first == "cognac")
		{
			GLuint locVertex, locNormal, locTexCoords;

			// get slot numbers
			locVertex = it->second->material->shader->getAttribLocation("vertex");
			locNormal = it->second->material->shader->getAttribLocation("normal");
			locTexCoords = it->second->material->shader->getAttribLocation("texCoords0");

			glGenVertexArrays(1, &(it->second->vao));
			glBindVertexArray(it->second->vao);

			// Vertices
			glBindBuffer(GL_ARRAY_BUFFER, it->second->bufVertices);
			glEnableVertexAttribArray(locVertex);
			glVertexAttribPointer(locVertex, 4, GL_FLOAT, GL_FALSE, 0, NULL);

			// Normals
			glBindBuffer(GL_ARRAY_BUFFER, it->second->bufNormals);
			glEnableVertexAttribArray(locNormal);
			glVertexAttribPointer(locNormal, 4, GL_FLOAT, GL_FALSE, 0, NULL);

			// Textures
			glBindBuffer(GL_ARRAY_BUFFER, it->second->bufTextureCoords);
			glEnableVertexAttribArray(locTexCoords);
			glVertexAttribPointer(locTexCoords, 2, GL_FLOAT, GL_FALSE, 0, NULL);

			glBindVertexArray(0);
		}
	}
}

void OpenGLInitializer::StartMainLoop()
{
	glutMainLoop();
}

