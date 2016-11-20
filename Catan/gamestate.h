#pragma once

#define NUMBER_OF_NODES		54
#define NUMBER_OF_TILES		19
#define NUMBER_OF_ROLLS		11
#define NODES_PER_TILE		6
#define NUMBER_OF_PLAYERS	4

struct Tile
{
	Resource type;
	unsigned int roll;
	std::string odds;

	unsigned int nodes[6];

	Tile() : type(Resource::NumResources), roll(0), odds("") {}
	Tile(Resource type, unsigned int roll);

	std::string GetType() const;
	std::string GetRoll() const;
};

struct Node
{
	Building building;
	Port port;
	int owningPlayer;

	Node()
		: building(Building::None), port(Port::NoPort), owningPlayer(-1)
	{}
};

class GameState
{
public:
	static GameState* GetState();

	static void Setup();
	static void CleanUp();

	void Place(char type, int source, int destination);
	void EndTurn();

	void AddTile(const Tile& tile);

	std::string& GetBoard();

	Player GetCurrentPlayer();
	int GetCurrentPlayerId();
	int GetCurrentPlayerColor();

private:
	GameState();

private:
	static GameState* state;

	std::string board;
	int currentPlayer;

	Player players[NUMBER_OF_PLAYERS];
	Tile tiles[NUMBER_OF_ROLLS][2];
	Node nodes[NUMBER_OF_NODES];
};
