#pragma once
class EventHandler
{
public:
	EventHandler();
	~EventHandler();

	void KeyDown(int c, int x, int y);
	void KeyUp(int c, int x, int y);
};

