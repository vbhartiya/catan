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

void Player::AddResource(Resource type, int number)
{
	resources[type] += number;
}

void Player::TakeResource(Resource type, int number)
{
	resources[type] -= number;
}


bool Player::CanBuild(Building item)
{
	switch (item)
	{
	case None:
		return false;
	case Settlement:
		return resources[Grain] >= 1 &&
			   resources[Brick] >= 1 &&
			   resources[Lumber] >= 1 &&
			   resources[Wool] >= 1;
	case City:
		return resources[Grain] >= 2 &&
			   resources[Ore] >= 3;
	case Road:
		return resources[Brick] >= 1 &&
			   resources[Lumber] >= 1;
	case DevelopementCard:
		return resources[Ore] >= 1 &&
			   resources[Grain] >= 1 &&
			   resources[Wool] >= 1;
	}
	return false;
}

void Player::Build(Building item)
{
	switch (item)
	{
	case None:
		return;

	case Settlement:
		resources[Grain] -= 1;
		resources[Brick] -= 1;
		resources[Lumber] -= 1;
		resources[Wool] -= 1;
		break;

	case City:
		resources[Grain] -= 2;
		resources[Ore] -= 3;
		break;

	case Road:
		resources[Brick] -= 1;
		resources[Lumber] -= 1;
		break;

	case DevelopementCard:
		resources[Ore] -= 1;
		resources[Grain] -= 1;
		resources[Wool] -= 1;
		break;
	}
}

unsigned int Player::GetResourceCount(Resource res) const
{
	return resources[res];
}
