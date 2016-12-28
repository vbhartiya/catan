#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

#include <ctype.h>
#include <Windows.h>

#include "enums.h"
#include "command.h"
#include "board.h"
#include "player.h"
#include "gamestate.h"
#include "renderer.h"

void Exec_Print(const strvec& params)
{
	if (params.size() != 2)
	{
		printf("[ERROR] Incorrect number of arguments for Print\n");
		return;
	} 
	
	if (params[1] == "board")
	{
		PrintBoard(GameState::GetState()->GetBoard());
	} 
	else if (params[1] == "resources")
	{
		GameState::GetState()->GetCurrentPlayer()->PrintResources();
	}
	else if (params[1] == "costs")
	{
		printf(COSTS, "Road", "Settlement", "City", "Developement Card");
	}
}

void Exec_Build(const strvec& params)
{
	if (params.size() < 3 || params.size() > 4)
	{
		printf("[ERROR] Incorrect number of arguments for Place\n");
		return;
	}

	int src = atoi(params[2].c_str());
	if (src < 1 || src > 54)
	{
		printf("[ERROR] Source value must be between 01 and 54 (inclusive)\n");
		return;
	}
	
	GameState* state = GameState::GetState();

	if (params[1] == "road")
	{
		if (params.size() < 4)
		{
			printf("[ERROR] Placing a road requires a source and destination\n");
			return;
		}

		int dst = atoi(params[3].c_str());

		if (dst < 1 || dst > 54)
		{
			printf("[ERROR] Destination value must be between 01 and 54 (inclusive)\n");
			return;
		}

		state->Build('r', src, dst);
	}
	else
	{
		if (params[1] == "city")
		{
			state->Build('c', src, 0);
		}
		else if (params[1] == "settlement")
		{
			state->Build('s', src, 0);
		}
		else
		{
			printf("[ERROR] Invalid parameter\n");
			return;
		}
	}
	
}

void Exec_Roll(const strvec& params)
{
	if (GameState::GetState()->IsSetupPhase())
	{
		printf("Cannot roll during setup!\n");
		return;
	}

	int die1, die2;
	for (int i = 0; i < 20; i++)
	{
		die1 = (rand() % 6) + 1;
		die2 = (rand() % 6) + 1;
		printf("\t%d, %d\r", die1, die2);
		Sleep(50);
	}
	printf("\n");

	GameState::GetState()->DistributeResources(die1 + die2);
}

void Exec_Reset(const strvec& params)
{
	GameState::GetState()->Setup();
}

void Exec_EndTurn(const strvec& params)
{
	GameState::GetState()->EndTurn();
}

void Exec_Help(const strvec& params)
{
#undef FUNC
#define FUNC(x, usage) printf("%10s " usage "\n", #x);

	COMMANDS
}

std::string ToLowerString(const std::string& str)
{
	std::string lowered(str);
	std::transform(str.begin(), str.end(), lowered.begin(), tolower);

	return lowered;
}

bool Execute(const strvec& arguments)
{
#undef FUNC
#define FUNC(x, usage) else if(ToLowerString(#x) == arguments[0]) Exec_##x(arguments);

	if (arguments[0] == "exit")
	{
		return false;
	}
	COMMANDS
	else
	{
		printf("[ERROR] Unrecognized command\n");
		Exec_Help(arguments);
	}

	return true;
}

void ParseCommand(const char* command, std::vector<std::string>& arguments)
{
	for (unsigned int i = 0, c = 0; command[i] != '\0'; i++)
	{
		if (command[i] == ' ')
		{
			c++;
			arguments.push_back("");
		}
		else
		{
			arguments[c] += tolower(command[i]);
		}
	}
}

void MainLoop()
{
	char command[1024];

	GameState* state = GameState::GetState();
	
	GameState::Setup();

	while (true)
	{
		GameState* state = GameState::GetState();
		std::string player = "Player " + std::to_string(state->GetCurrentPlayerId() + 1) + "> ";

		PrintColoredText(state->GetCurrentPlayerColor(), player.c_str());
		std::cin.getline(command, 1024);
		
		std::vector<std::string> arguments(1);
		ParseCommand(command, arguments);

		if (!Execute(arguments))
			break;
	}

	GameState::CleanUp();
}

void RobberLoop()
{
	char command[128];
	int id = 0;

	// Loop to move the robber
	while (true)
	{
		printf("Move Robber to (Tile ID) : ");
		std::cin.getline(command, 128);

		id = atoi(command);

		if (id < 1 || id > NUMBER_OF_TILES)
		{
			printf("Tile ID must be between 01 and %d\n", NUMBER_OF_TILES);
		}
		else if (GameState::GetState()->GetRobberTile() == id)
		{
			printf("You must move the robber to a different tile\n");
		}
		else
		{
			GameState::GetState()->SetRobberTile(id);
			break;
		}
	}

	// Loop to choose which player to steal from
}
