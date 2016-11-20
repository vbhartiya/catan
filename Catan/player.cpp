#include <string>

#include "enums.h"
#include "player.h"

Player::Player()
{
	for (int i = 0; i < NumResources; i++)
		resources[i] = 0;
}

void Player::PrintResources()
{
	for(int i = 0; i < NumResources; i++)
	{
		if ((Resource)i == Desert) continue;

		printf("%8s | %d\n", ResourceToString((Resource)i), resources[i]);
	}
}
