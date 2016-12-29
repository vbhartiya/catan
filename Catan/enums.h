#pragma once

enum Resource { Desert, Grain, Brick, Wool, Lumber, Ore, NumResources };
enum Building { None, Settlement, City, Road, DevelopementCard, NumBuildings };
enum Port { NoPort, AnyPort, GrainPort, BrickPort, WoolPort, LumberPort, OrePort };

static char* ResourceToString(Resource res, bool caps = false)
{
	switch (res)
	{
	case Desert:
		return caps ? "DESERT" : "Desert";
	case Grain:
		return caps ? "GRAIN " : "Grain";
	case Brick:
		return caps ? "BRICK " : "Brick";
	case Lumber:
		return caps ? "LUMBER" : "Lumber";
	case Ore:
		return caps ? " ORE  " : "Ore";
	case Wool:
		return caps ? " WOOL " : "Wool";
	}

	return "";
}

static Resource StringToResource(const std::string& res)
{
	std::string lowRes = ToLowerString(res);

	if (lowRes == "desert")
	{
		return Desert;
	} 
	else if (lowRes == "grain")
	{
		return Grain;
	}
	else if (lowRes == "brick")
	{
		return Brick;
	}
	else if (lowRes == "lumber")
	{
		return Lumber;;
	}
	else if (lowRes == "ore")
	{
		return Ore;
	}
	else if (lowRes == "wool")
	{
		return Wool;
	}

	return NumResources;
}
