#pragma once
class Alcohol
{
public:
	Alcohol(int volume, int power);
	~Alcohol();
	int volume; // 0 - 1000 (niech to bêd¹ mililitry)
	int power; // 0 - 100 (niech to bêdzie zawartoœæ alkoholu w procentach)
	int volumeConst;
	void reset(); //przywroc mililitry
};

