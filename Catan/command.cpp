#include <string>
#include <vector>
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
		GameState::GetState()->GetCurrentPlayer().PrintResources();
	}
}

void Exec_Place(const strvec& params)
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

		state->Place('r', src, dst);
	}
	else
	{
		if (params[1] == "city")
		{
			state->Place('c', src, 0);
		}
		else if (params[1] == "settlement")
		{
			state->Place('s', src, 0);
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

bool Execute(const strvec& arguments)
{

#undef FUNC
#define FUNC(x, usage) else if(#x == arguments[0]) Exec_##x(arguments);

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
			arguments[c] += (command[i]);
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
