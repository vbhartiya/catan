#include <string>
#include <time.h>

#include "enums.h"
#include "player.h"
#include "gamestate.h"
#include "board.h"


std::string Tile::GetRoll() const
{
	if (roll == 0)
		return "  ";

	char buffer[3];
	sprintf_s(buffer, "%02d", roll);

	return std::string(buffer);
}

std::string InitRandomBoard()
{
	srand((unsigned int)time(NULL));

	int maxTypeOfResource[] = { 1, 4, 3, 4, 4, 3 };
	int maxRollValues[] = { 1, 2, 2, 2, 2, 0, 2, 2, 2, 2, 1 };

	unsigned int tileNodes[NUMBER_OF_TILES][NODES_PER_TILE] = { { 1, 2, 4, 5, 9,10},
																{ 3, 4, 8, 9,14,15},
																{ 5, 6,10,11,16,17},
																{ 7, 8,13,14,19,20},
																{ 9,10,15,16,21,22},
																{11,12,17,18,23,24},
																{14,15,20,21,26,27},
																{16,17,22,23,28,29},
																{19,20,25,26,31,32},
																{21,22,27,28,33,34},
																{23,24,29,30,35,36},
																{26,27,32,33,38,39},
																{28,29,34,35,40,41},
																{31,32,37,38,43,44},
																{33,34,39,40,45,46},
																{35,36,41,42,47,48},
																{38,39,44,45,49,50},
																{40,41,46,47,51,52},
																{45,46,50,51,53,54} };

	int numberOfTiles = 19;

	GameState* state = GameState::GetState();

	std::string board(BOARD);

	for (int i = 0; i < numberOfTiles; i++)
	{
		Resource type = (Resource)(rand() % (int)NumResources);

		while (maxTypeOfResource[type] <= 0)
		{
			type = (Resource)(rand() % (int)NumResources);
		}

		maxTypeOfResource[type]--;

		unsigned int roll = rand() % 11;

		if (type != Desert)
		{
			while (maxRollValues[roll] <= 0)
			{
				roll = rand() % 11;
			}

			maxRollValues[roll]--;
		}

		Tile t(type, roll+2);

		memcpy(t.nodes, tileNodes[i], sizeof(unsigned int) * NODES_PER_TILE);

		state->AddTile(t);

		ReplaceSubstring(board, "TTTTTT", t.GetType().c_str(), 6, 1);
		ReplaceSubstring(board, "00", t.GetRoll().c_str(), 2, 1);
		ReplaceSubstring(board, ".....", t.odds.c_str(), 5, 1);
	}

	return board;
}

bool ReplaceSubstring(std::string& input, const char* original, const char* replacement, size_t length, unsigned int ocurrence)
{
	size_t index = 0;
	unsigned int count = 1;

	bool changed = false;

	while (true) {

		index = input.find(original, index);
		if (index == std::string::npos) break;

		if (ocurrence > 0)
		{
			if (count == ocurrence)
			{
				input.replace(index, length, replacement);
				changed = true;
				break;
			}
			else
			{
				count++;
				index += length;
			}
		}
		else
		{
			input.replace(index, length, replacement);
			index += length;
			changed = true;
		}
	}

	return changed;
}