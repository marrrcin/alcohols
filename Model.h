#pragma once
class Model
{
public:
	Model();
	~Model();
	virtual void Draw() = 0;
	virtual void NextFrame() = 0;
};

