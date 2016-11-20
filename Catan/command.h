#pragma once

typedef std::vector<std::string> strvec;

#define FUNC(x, usage) void Exec_##x(const strvec& params);

#define COMMANDS FUNC(Print, "<board, resources>")\
				 FUNC(Place, "<road, settlement, city> <vertex id> [destination id]")\
				 FUNC(Roll, "<>")\
				 FUNC(EndTurn, "<>")\
				 FUNC(Reset, "<>" )\
				 FUNC(Help, "<>")

COMMANDS

void MainLoop();