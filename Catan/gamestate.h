#pragma once

#define NUMBER_OF_NODES		54
#define NUMBER_OF_TILES		19
#define NUMBER_OF_ROLLS		11
#define NODES_PER_TILE		6
#define NUMBER_OF_PLAYERS	4
#define MAX_TILES_PER_ROLL	2

typedef std::vector< std::vector <std::string> > logvec;

struct Tile
{
	Resource type;
	unsigned int roll;
	unsigned int id;
	std::string odds;

	unsigned int nodes[NODES_PER_TILE];

	Tile() : type(Resource::NumResources), roll(0), id(0), odds("") {}
	Tile(unsigned int id, Resource type, unsigned int roll);

	std::string GetType() const;
	std::string GetRoll() const;
};

struct Node
{
	Building building;
	Port port;
	int owningPlayer;

	std::map<int, int> neighbours; // The second int represents if there is a road between this node and it's neighbour, and who owns it.

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

	void Build(char type, int source, int destination);
	void EndTurn();

	void AddTile(const Tile& tile);
	void SetRobberTile(unsigned int id);

	std::string& GetBoard();
	void DistributeResources(int roll);
	void TradeResources(const resmap& toGive, const resmap& toTake, int playerID);

	void PrintHistory() const;
	void PrintLastTurn() const;
	Player* GetCurrentPlayer();
	int GetCurrentPlayerId() const;
	int GetCurrentPlayerColor() const;
	int GetRobberTile() const;
	bool IsSetupPhase() const;

private:
	GameState();

private:
	static GameState* state;

	std::string board;
	int currentPlayer;
	bool setupPhase;
	bool reverse;
	int robber;

	logvec history;
	int turnid;

	Player players[NUMBER_OF_PLAYERS];
	Tile tiles[NUMBER_OF_ROLLS][MAX_TILES_PER_ROLL];
	Node nodes[NUMBER_OF_NODES];
};
