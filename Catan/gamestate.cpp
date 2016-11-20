
#include <string>

#include "board.h"
#include "enums.h"
#include "player.h"
#include "renderer.h"
#include "gamestate.h"

static char colorChars[] = { 'R', 'C', 'Y', 'G' };
static int colorInts[] = { 12, 11, 14, 10 };


Tile::Tile(Resource type, unsigned int roll)
{
	this->type = type;
	if (type == Desert)
	{
		this->roll = 0;
		this->odds = "     ";
	}
	else
	{
		this->roll = roll;

		switch (roll)
		{
		case 2:
		case 12:
			odds = " '   ";
			break;
		case 3:
		case 11:
			odds = " ''  ";
			break;
		case 4:
		case 10:
			odds = "'''  ";
			break;
		case 5:
		case 9:
			odds = "'''' ";
			break;
		case 6:
		case 8:
			odds = "'''''";
			break;
		}
	}
}

std::string Tile::GetType() const
{
	return ResourceToString(type, true);
}

GameState* GameState::state = nullptr;

GameState::GameState()
{
	board = "";
	currentPlayer = -1;
	setupPhase = true;
}

GameState* GameState::GetState()
{
	if (!state)
	{
		state = new GameState();
	}

	return state;
}

void GameState::Setup()
{
	state->board = InitRandomBoard();
	state->currentPlayer = 0;
	state->setupPhase = true;

	for (int i = 0; i < NUMBER_OF_NODES; i++)
	{
		state->nodes[i] = Node();

		// Set up ports
			 if (i ==  0 || i ==  1) state->nodes[i].port = AnyPort;
		else if (i ==  2 || i ==  7) state->nodes[i].port = OrePort;
		else if (i ==  5 || i == 10) state->nodes[i].port = WoolPort;
		else if (i == 18 || i == 24) state->nodes[i].port = GrainPort;
		else if (i == 23 || i == 29) state->nodes[i].port = AnyPort;
		else if (i == 36 || i == 42) state->nodes[i].port = AnyPort;
		else if (i == 41 || i == 47) state->nodes[i].port = AnyPort;
		else if (i == 48 || i == 49) state->nodes[i].port = LumberPort;
		else if (i == 50 || i == 51) state->nodes[i].port = BrickPort;
	}
}

void GameState::CleanUp()
{
	delete state;
}

std::string& GameState::GetBoard()
{
	return board;
}

void GameState::DistributeResources(int roll)
{
	char buffer[16];
	sprintf_s(buffer, "Player %d", currentPlayer + 1);

	PrintColoredText(colorInts[currentPlayer], buffer);

	printf(" rolled %d\n\n", roll);

	if (roll == 7)
	{
		/// TODO : Add mechanics for robber
		return;
	}

	for (int i = 0; i < MAX_TILES_PER_ROLL; i++)
	{
		Tile &t = tiles[roll - 2][i];
		if (t.type == NumResources) continue;

		for (int j = 0; j < NODES_PER_TILE; j++)
		{
			int nodeIndex = t.nodes[j] - 1;
			if (nodes[nodeIndex].owningPlayer > -1)
			{
				int playerIndex = nodes[nodeIndex].owningPlayer;

				players[playerIndex].AddResource(t.type, (nodes[nodeIndex].building == City) ? 2 : 1);
			}
		}
	}
}

Player GameState::GetCurrentPlayer()
{
	return players[currentPlayer];
}

int GameState::GetCurrentPlayerId()
{
	return currentPlayer;
}

int GameState::GetCurrentPlayerColor()
{
	return colorInts[currentPlayer];
}

void GameState::Build(char type, int source, int destination)
{
	if (source > destination && destination > 0)
	{
		int tmp = source;
		source = destination;
		destination = tmp;
	}

	char substring[8], replacement[8];

	bool updated = false;
	
	switch (type)
	{
	case 'r':
		if (!setupPhase && !GetCurrentPlayer().CanBuild(Road))
		{
			printf("Not enough resources to build a road.");
		}

		sprintf_s(substring, "[%02d%02dB", source, destination);
		sprintf_s(replacement, "[%02d%02d%c", source, destination, colorChars[currentPlayer]);

		if (ReplaceSubstring(board, substring, replacement, 6))
		{
			GetCurrentPlayer().Build(Road);
		}
		break;

	case 's':
		if (!setupPhase && !GetCurrentPlayer().CanBuild(Settlement))
		{
			printf("Not enough resources to build a settlement.");
		}

		sprintf_s(substring, "[N%02dNB]", source);
		sprintf_s(replacement, "[N%02d%c%c]", source, colorChars[currentPlayer], 'S');

		if (ReplaceSubstring(board, substring, replacement, 7))
		{
			nodes[source - 1].building = Settlement;
			nodes[source - 1].owningPlayer = currentPlayer;

			GetCurrentPlayer().Build(Settlement);
		}
		break;

	case 'c':
		if (!setupPhase && !GetCurrentPlayer().CanBuild(City))
		{
			printf("Not enough resources to build a city.");
		}

		sprintf_s(substring, "[N%02d%cS]", source, colorChars[currentPlayer]);
		sprintf_s(replacement, "[N%02d%c%c]", source, colorChars[currentPlayer], 'C');

		if (ReplaceSubstring(board, substring, replacement, 7))
		{
			nodes[source - 1].building = City;

			GetCurrentPlayer().Build(City);
		}
		break;
	}
}

void GameState::EndTurn()
{
	currentPlayer = (currentPlayer + 1) % NUMBER_OF_PLAYERS;
}

void GameState::AddTile(const Tile & tile)
{
	if (tile.type == Resource::Desert)
	{
		tiles[7 - 2][0] = tile;
	}
	else
	{
		if (tiles[tile.roll - 2][0].type == Resource::NumResources)
		{
			tiles[tile.roll - 2][0] = tile;
		}
		else
		{
			tiles[tile.roll - 2][1] = tile;
		}
	}
}
