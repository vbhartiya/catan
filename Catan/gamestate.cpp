#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#include "utility.h"
#include "board.h"
#include "enums.h"
#include "player.h"
#include "renderer.h"
#include "command.h"
#include "gamestate.h"

static char colorChars[] = { 'R', 'C', 'Y', 'G' };
static int colorInts[] = { 12, 11, 14, 10 };


Tile::Tile(unsigned int id, Resource type, unsigned int roll)
{
	this->id = id;
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

GameState::GameState() :
	board(""),
	currentPlayer(-1),
	setupPhase(true),
	reverse(false),
	turnid(0)
{
	history.push_back(strvec());
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

	ParseNodeNeighbours(state->nodes, state->board);
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
	history[turnid].push_back("Player " + std::to_string(currentPlayer + 1) + " rolled " + std::to_string(roll) + ".");

	if (roll == 7)
	{
		RobberLoop();
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
				int amount = (nodes[nodeIndex].building == City) ? 2 : 1;

				players[playerIndex].AddResource(t.type, amount);
				history[turnid].push_back("Player " + std::to_string(playerIndex + 1) + " received " + std::to_string(amount) + " " + ResourceToString(t.type) + ".");
			}
		}
	}
}

void GameState::TradeResources(const resmap & toGive, const resmap & toTake, int playerID)
{
	// Check that current player has enough resources
	for (std::pair<Resource, unsigned int> p : toGive)
	{
		if (p.second < 1)
		{
			printf("Invalid amount for resource.\n");
			return;
		}
		if (players[currentPlayer].GetResourceCount(p.first) < p.second)
		{
			printf("Not enough resources to trade.\n");
			return;
		}
	}
	
	// Confirm the trade with the second player
	if (!ConfirmTrade(toGive, toTake, colorInts[playerID - 1]))
	{
		printf("Player %d rejected the trade.\n", playerID);
		return;
	}
	
	// Check that the second player has enough resources
	for (std::pair<Resource, unsigned int> p : toTake)
	{
		if (p.second < 1)
		{
			printf("Invalid amount for resource.\n");
			return;
		}
		if (players[playerID - 1].GetResourceCount(p.first) < p.second)
		{
			printf("Not enough resources to trade.\n");
			return;
		}
	}

	// Perform the trade
	std::stringstream s;
	s << "Player " << (currentPlayer + 1) << " traded ";
	for (std::pair<Resource, unsigned int> p : toGive)
	{
		players[currentPlayer].TakeResource(p.first, p.second);
		players[playerID - 1].AddResource(p.first, p.second);

		s << p.second << " " << ResourceToString(p.first) << ", ";
	}
	s.seekp(-2, std::ios_base::cur);

	s << " to Player " << playerID << " for ";

	for (std::pair<Resource, unsigned int> p : toTake)
	{
		players[currentPlayer].AddResource(p.first, p.second);
		players[playerID - 1].TakeResource(p.first, p.second);

		s << p.second << " " << ResourceToString(p.first) << ", ";
	}
	s.seekp(-2, std::ios_base::cur);
	s << ".  ";

	history[turnid].push_back(s.str());	
}

void GameState::PrintHistory() const
{
	printf("==================================================\n");
	for (int i = 0; i < history.size(); i++)
	{
		if (history[i].size() > 0)
		{
			printf("Turn %d:\n", i + 1);
			for (std::string s : history[i])
			{
				printf("\t%s\n", s.c_str());
			}
		}
	}
	printf("==================================================\n");
}

void GameState::PrintLastTurn() const
{
	printf("==================================================\n");
	if (history[turnid - 1].size() > 0)
	{
		printf("Turn %d:\n", (turnid - 1) + 1);
		for (std::string s : history[turnid - 1])
		{
			printf("\t%s\n", s.c_str());
		}
	}
	printf("==================================================\n");
}

Player* GameState::GetCurrentPlayer()
{
	return &players[currentPlayer];
}

int GameState::GetCurrentPlayerId() const
{
	return currentPlayer;
}

int GameState::GetCurrentPlayerColor() const
{
	return colorInts[currentPlayer];
}

int GameState::GetRobberTile() const
{
	return state->robber;
}

bool GameState::IsSetupPhase() const
{
	return setupPhase;
}

void GameState::Build(char type, int source, int destination)
{
	if (source > destination && destination > 0)
	{
		int tmp = source;
		source = destination;
		destination = tmp;
	}

	source--;
	destination--;

	char substring[8], replacement[8];

	bool updated = false;
	
	switch (type)
	{
	case 'r':
	{
		if (!setupPhase && !GetCurrentPlayer()->CanBuild(Road))
		{
			printf("Not enough resources to build a road.\n");
			return;
		}

		if (!IsValidRoad(board, source + 1, destination + 1))
		{
			printf("No valid road found between %02d and %02d\n", source + 1, destination + 1);
			return;
		}

		bool prevRoadExists = false;
		for (auto itr = nodes[source].neighbours.begin(); itr != nodes[source].neighbours.end(); itr++)
		{
			if (itr->second == currentPlayer)
			{
				prevRoadExists = true;
			}
		}

		if (!prevRoadExists)
		{
			for (auto itr = nodes[destination].neighbours.begin(); itr != nodes[destination].neighbours.end(); itr++)
			{
				if (itr->second == currentPlayer)
				{
					prevRoadExists = true;
				}
			}
		}

		if (nodes[source].owningPlayer != currentPlayer && nodes[destination].owningPlayer != currentPlayer && !prevRoadExists)
		{
			printf("Roads must be build from a settlement or city, or continue another road.\n");
			return;
		}

		sprintf_s(substring, "[%02d%02dB", source + 1, destination + 1);
		sprintf_s(replacement, "[%02d%02d%c", source + 1, destination + 1, colorChars[currentPlayer]);

		if (ReplaceSubstring(board, substring, replacement, 6))
		{
			nodes[source].neighbours[destination] = currentPlayer;
			nodes[destination].neighbours[source] = currentPlayer;
			GetCurrentPlayer()->Build(Road);

			history[turnid].push_back("Player " + std::to_string(currentPlayer + 1) + " built a road from " + std::to_string(source + 1) + " to " + std::to_string(destination + 1) + ".");
		}
		break;
	}
	case 's':
	{
		if (!setupPhase)
		{
			if (!GetCurrentPlayer()->CanBuild(Settlement))
			{
				printf("Not enough resources to build a settlement.\n");
				return;
			}

		}

		bool roadExists = false;
		for (auto itr = nodes[source].neighbours.begin(); itr != nodes[source].neighbours.end(); itr++)
		{
			if (nodes[itr->first].owningPlayer != -1)
			{
				printf("Cannot build a settlement at %02d since %02d is already occupied.\n", source + 1, itr->first + 1);
				return;
			}

			if (itr->second == currentPlayer)
			{
				roadExists = true;
			}
		}

		if (!setupPhase && !roadExists)
		{
			printf("Cannot build a settlement as no usable roads lead to %02d.\n", source + 1);
			return;
		}

		sprintf_s(substring, "[N%02dNB]", source + 1);
		sprintf_s(replacement, "[N%02d%c%c]", source + 1, colorChars[currentPlayer], 'S');

		if (ReplaceSubstring(board, substring, replacement, 7))
		{
			nodes[source].building = Settlement;
			nodes[source].owningPlayer = currentPlayer;

			GetCurrentPlayer()->Build(Settlement);

			history[turnid].push_back("Player " + std::to_string(currentPlayer + 1) + " built a settlement at " + std::to_string(source + 1) + ".");
		}
		break;
	}
	case 'c':
		if (!setupPhase && !GetCurrentPlayer()->CanBuild(City))
		{
			printf("Not enough resources to build a city.\n");
		}

		sprintf_s(substring, "[N%02d%cS]", source + 1, colorChars[currentPlayer]);
		sprintf_s(replacement, "[N%02d%c%c]", source + 1, colorChars[currentPlayer], 'C');

		if (ReplaceSubstring(board, substring, replacement, 7))
		{
			nodes[source].building = City;

			GetCurrentPlayer()->Build(City);
			history[turnid].push_back("Player " + std::to_string(currentPlayer + 1) + " upgraded the settlement at " + std::to_string(source + 1) + " to a city.");
		}
		break;
	}
}

void GameState::EndTurn()
{
	if (setupPhase)
	{
		if(players[currentPlayer].GetBuiltItemCount(Settlement) < ((reverse) ? 2U : 1U) ||
		   players[currentPlayer].GetBuiltItemCount(Road) < ((reverse) ? 2U : 1U))
		{
			printf("You must build 1 settlement and 1 road.\n");
			return;
		}

		// If we're at the first player in reverse, then this is the last turn of the setup phase
		if (currentPlayer == 0 && reverse)
		{
			reverse = false;
			setupPhase = false;
			return;
		}
		// if we're at the last player, then we need to go in reverse order
		else if (currentPlayer == NUMBER_OF_PLAYERS - 1 && !reverse)
		{
			reverse = true;
			return;
		}

		if (reverse)
		{
			currentPlayer = (currentPlayer - 1) % NUMBER_OF_PLAYERS;
			return;
		}
	}

	currentPlayer = (currentPlayer + 1) % NUMBER_OF_PLAYERS;

	turnid++;
	history.push_back(strvec());
}

void GameState::AddTile(const Tile & tile)
{
	if (tile.type == Resource::Desert)
	{
		tiles[7 - 2][0] = tile;
		state->robber = tile.id;
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

void GameState::SetRobberTile(unsigned int id)
{
	state->robber = id;
	history[turnid].push_back("Player " + std::to_string(currentPlayer + 1) + " moved the robber to " + std::to_string(id) + ".");
}

