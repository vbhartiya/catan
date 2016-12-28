#pragma once

class Player
{
public:
	Player();

	void PrintResources();
	void AddResource(Resource type, int number);
	void TakeResource(Resource type, int number);

	bool CanBuild(Building item);
	void Build(Building item);

	unsigned int GetBuiltItemCount(Building building) const;
	unsigned int GetResourceCount(Resource res) const;
private:
	unsigned int resources[NumResources];
	std::map<Building, unsigned int> builtItems;
};