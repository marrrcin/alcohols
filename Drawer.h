#pragma once
class Drawer
{
	
public:
	Drawer();
	~Drawer();

	void Display();
	void PrepareNextFrame();

	void CreateObjectsToDraw();

	std::map<std::string, Model*> objectsToDraw;
};

