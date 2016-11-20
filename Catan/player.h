#pragma once

class Player
{
public:
	Player();

	void PrintResources();
private:
	unsigned int resources[NumResources];
};