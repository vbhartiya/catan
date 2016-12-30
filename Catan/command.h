#pragma once

typedef std::vector<std::string> strvec;
typedef std::vector<std::string>::const_iterator svitr;
typedef std::map<Resource, unsigned int> resmap;

#define FUNC(x, usage) void Exec_##x(const strvec& params);

#define COMMANDS FUNC(Print, "<board, resources, costs, history, lastturn>")\
				 FUNC(Build, "<road, settlement, city> <vertex id> [destination id]")\
				 FUNC(Trade, "<resources> for <resources> with Player <player id>")\
				 FUNC(Roll, "<>")\
				 FUNC(EndTurn, "<>")\
				 FUNC(Reset, "<>" )\
				 FUNC(Help, "<>")

COMMANDS

void MainLoop();
void RobberLoop();
bool ConfirmTrade(const resmap& toGive, const resmap& toTake, int color);