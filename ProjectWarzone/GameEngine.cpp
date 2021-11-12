#include "GameEngine.h"
#include <vector>
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "MapDriver.h"

using namespace Engine;
using namespace std;

//Start the program with the current state pointer at null.
GameState* GameState::current = nullptr;
GameState** GameState::states = nullptr;

void GameState::SwitchState(GameState& newState) {
	GameState::current->Exit();
	GameState::current = &newState;
	GameState::current->Setup();
}

using namespace States;

void GameState::GameSetup() {
	cout << "Game Setup...\n\tInitializing states...\n";

	//Initialize all game states.
	GameState::states = new GameState*[8]{
		new Start,
		new LoadMap,
		new ValidMap,
		new AddPlayers,
		new AssignReinf,
		new IssueOrders,
		new ExecOrders,
		new GameOver
	};

	cout << "\tEstablishing state links...\n";
	//Establish links between states.
	states[0]->links = { states[1] };
	states[1]->links = { states[1], states[2] };
	states[2]->links = { states[3] };
	states[3]->links = { states[3], states[4] };
	states[4]->links = { states[5] };
	states[5]->links = { states[5], states[6] };
	states[6]->links = { states[6], states[4], states[7] };
	states[7]->links = { states[0] };

	cout << "\tMoving to start state...\n";
	//Set the starting game state and call its setup function.
	GameState::current = states[0];
	GameState::current->Setup();
	cout << "Ready.\n\n";
}

void GameState::GameExit() {
	cout << "\n\nGame Exit...\n\tDeleting states...\n";
	//Loop through each element element of the array of pointers, de-allocating each.
	for (short i = 0; i < 8; i++) {
		delete *(GameState::states + i);
	}
	cout << "\tDe-allocating pointer array...\n";

	//De-allocate the array itself.
	delete GameState::states;
	cout << "Done.\n";
}


#pragma region State Constructors

//Base class default and initialization constructor.
//Default parameters are declared in header file.
GameState::GameState(string stateName, vector<string> cmds) : name(stateName), commands(cmds) { }
//Base class copy constructor.
GameState::GameState(GameState& toCopy) : name(toCopy.name), links(toCopy.links), commands(toCopy.commands) { }

//Base class destructor.
GameState::~GameState() {
	//Remove each pointer.
	for (short i = 0; i < links.size(); i++) {
		links.at(i) = nullptr;
	}
	cout << "\t\tDeleted state: " << this->name << "\n";
}


//Derived class default constructors.
//Funky table indentation. Hopefully easier to read.
Start::Start():				GameState(	"Start",				{ "loadmap" }				) { }
LoadMap::LoadMap():			GameState(	"Loaded Map",			{ "loadmap", "validatemap" }		) { }
ValidMap::ValidMap():		GameState(	"Validated Map",		{ "addplayer" }				) { }
AddPlayers::AddPlayers():	GameState(	"Add Players",			{ "addplayer", "gamestart" }	) { }
AssignReinf::AssignReinf():	GameState(	"Assign Reinforcements",{ "issueorder" }			) { }
IssueOrders::IssueOrders():	GameState(	"Issue Orders",			{ "issueorder", "endissueorders" }	) { }
ExecOrders::ExecOrders():	GameState(	"Execute Orders",		{ "execorder", "endexecorders", "win" }	) { }
GameOver::GameOver():		GameState(	"Win",					{ "replay", "quit" }			) { }

//Again, there are no destructors for the derived
//classes since they define no members (see header file).

#pragma endregion


#pragma region State Behavior

//Base class stream insertion operator.
ostream& Engine::operator<<(ostream& out, GameState& state) {
	out << state.name << " state.\nCommands: " << state.cmdList();
	return out;
}
//Base class assignment operator.
void GameState::operator=(GameState& other) {
	this->name = other.name;
	this->links = other.links;
	this->commands = other.commands;
}


//Gets the list of available commands to switch states.
string GameState::cmdList() {
	string toReturn = "(";

	for (string cmd : this->commands) {
		toReturn += cmd + ", ";
	}
	//Remove the last two characters (comma + space).
	toReturn.pop_back();
	toReturn.pop_back();
	toReturn += ")";

	return toReturn;
}


//These will allow for custom behavior for every state on transition.
//Nothing for now.

void Start::Setup() {
	cout << *this << endl;
}
void Start::Exit() { }

void LoadMap::Setup() {
	cout << *this << endl;
}
void LoadMap::Exit() { }

void ValidMap::Setup() {
	cout << *this << endl;
}
void ValidMap::Exit() { }

void AddPlayers::Setup() {
	cout << *this << endl;
}
void AddPlayers::Exit() { }

void AssignReinf::Setup() {
	cout << *this << endl;
}
void AssignReinf::Exit() { }

void IssueOrders::Setup() {
	cout << *this << endl;
}
void IssueOrders::Exit() { }

void ExecOrders::Setup() {
	cout << *this << endl;
}
void ExecOrders::Exit() { }

void GameOver::Setup() {
	cout << *this << endl;
}
void GameOver::Exit() { }

void GameState::startupPhase(vector<Player*>* players, Deck* deck)
{
	GameSetup();

	cout << "The startup phase has been initiated..." << endl;

	Map mapToLoad;
	bool startupIsDone = false;
	while (!startupIsDone)
	{
		string inputCmd;
		bool validCmd = false;
		while (!validCmd)
		{
			cout << "Please enter a command" << endl;
			cin >> inputCmd;

			for (int i = 0; i < current->commands.size(); i++)
			{
				if (inputCmd == current->commands.at(i))
					validCmd = true;
			}

			if (!validCmd)
				cout << "Invalid command. Make sure that you are using a command that is valid in the current state" << endl;
		}

		if (inputCmd == "loadmap")
			mapToLoad = loadmapCmd();

		if (inputCmd == "validatemap")
			validatemapCmd(mapToLoad);

		if (inputCmd == "addplayer")
			addplayerCmd(players);

		if (inputCmd == "gamestart")
		{
			gamestartCmd(mapToLoad, players, deck);
			startupIsDone = true;
		}

		cout << endl;
	}

	// TODO: here prob ends with starting "play phase"
}

Map GameState::loadmapCmd()
{
	cout << "Now executing loadmap command..." << endl;
	string filename;

	cout << "Please enter the name of the map to load..." << endl;
	cin >> filename;

	Map map = readfile(filename);

	// Change current state to the "maploaded" state
	current = states[1];

	return map;
}

void GameState::validatemapCmd(Map map)
{
	cout << "Now executing validatemap command..." << endl;
	// Change current state to the "mapvalidated" state
	if (validate(map))
	{
		cout << "The map was validated. Now entering the mapvalidated state..." << endl;
		current = states[2];
	}
	else
		cout << "The map is invalid. Use the loadmap command to load a valid map..." << endl;
}

void GameState::addplayerCmd(vector<Player*>* players)
{
	cout << "Now executing addplayer command..." << endl;

	int numOfPlayers;
	cout << "How many players do you wish to add to the current game?\nYou can choose a number between 2 and 6" << endl;
	cin >> numOfPlayers;

	for (int i = 0; i < numOfPlayers; i++)
	{
		string playerName;

		cout << "Adding player " << (i + 1) << endl;
		cout << "Name of the new player: ";
		cin >> playerName;

		Player *player = new Player(playerName);

		cout << "Player" << *player <<  " was added to the game\n" << endl;

		players->push_back(player);
	}

	// Change current state to the "playersadded" state
	current = states[3];
}

void GameState::gamestartCmd(Map map, vector<Player*>* players, Deck* deck)
{
	cout << "Now executing gamestart command..." << endl;

	// Distributing the territories to the players
	int numOfTerrPerPlayer = map.getNumOfTerr() / players->size();
	int remainderOfTerrs = map.getNumOfTerr() - (numOfTerrPerPlayer * players->size());

	// This gives territories to the players but it's possible that there are still some unallocated territories
	// This happens if the remainder is not zero
	// At most, a player may have 1 territory more than another player
	// Note however that this is still quite fair since maps have a lot of territories (which means players have many territories overall as well)
	for (int i = 0; i < players->size(); i++)
		for (int j = 0; j < numOfTerrPerPlayer; j++)
			players->at(i)->addTerritories(map.getTerritory(j));

	if (remainderOfTerrs != 0)
	{
		for (int i = 0; i < remainderOfTerrs; i++)
			players->at(i)->addTerritories(map.getTerritory((numOfTerrPerPlayer * players->size()) + i));
	}

	// Randomly determining the order of play
	srand((unsigned int)time(NULL));

	// We first start by generating random numbers
	vector<int> nums;
	for (int i = 0; i < players->size(); i++)
	{
		nums.push_back(rand());
	}

	// Then we can determine the actual play order from those random numbers
	for (int i = 0; i < players->size(); i++)
	{
		int max = -1;
		int indexOfMax = -1;
		for (int j = 0; j < nums.size(); j++)
		{
			if (nums.at(j) > max)
			{
				max = nums.at(j);
				indexOfMax = j;
			}
		}

		players->at(indexOfMax)->setPlayOrder(new int(i + 1));
		nums.at(indexOfMax) = -1;
	}

	// Give 50 armies to each player
	for (int i = 0; i < players->size(); i++)
		players->at(i)->setReinF(50);

	// Each player draws two cards
	for (int i = 0; i < players->size(); i++)
		deck->draw(players->at(i)->getHand());
}

void mainGameLoop()
{
	vector<Player*> participants;
	Map map;
	Deck* deck = new Deck();
	bool ended = reinforcementPhase(map, participants);
	while (!ended)
	{
		//removing empty player if there is one
		for (int i = 0; i < participants.size(); i++)
		{
			if (participants[i]->getTerritories().size() == 0)
			{
				participants.erase(participants.begin() + i);
			}
		}
		issueOrderPhase(map, participants, deck);
		executeOrderPhase(map, participants);
		ended = reinforcementPhase(map, participants);
	}
	//must chage where the victory condition is
}


bool reinforcementPhase(Map m, vector<Player*>& participants)
{
	Player* tempOwner;
	//loop for all players to give players appropriate reinforcements base on territories owned / 3
	for (int i = 0; i < participants.size(); i++)
	{
		participants[i]->addReinF((participants[i]->getTerritories().size()) / 3);
	}
	//to get the continent bonus
	for (int i = 0; i < m.getNumOfCont(); i++)
	{
		tempOwner = m.getTerritory(m.getContinent(i)->getTerrID(0))->getOwner();
		bool getBonus = false;
		for (int j = 1; j < m.getContinent(i)->getLength(); j++)
		{
			if (m.getTerritory(m.getContinent(i)->getTerrID(j))->getOwner() != tempOwner)
			{
				getBonus = false;
				break;
			}
			else
			{
				getBonus = true;
			}
		}
		if (getBonus)
		{
			tempOwner->addReinF(m.getContinent(i)->getBonus());
		}
	}
	//cheking for map ownership as in to see if only one player owns it all
	tempOwner = m.getTerritory(0)->getOwner();
	bool won = false;
	for (int i = 1; i < m.getNumOfTerr(); i++)
	{
		if (m.getTerritory(i)->getOwner() != tempOwner)
		{
			won = false;
			break;
		}
		else
		{
			won = true;
		}
	}
	return won;
}

void issueOrderPhase(Map m, vector<Player*>& participants, Deck* deck)
{
	vector<int> reinf;
	vector<vector<territory*>> defend;
	vector<vector<territory*>> attack;
	int playersDone;
	for (int i = 0; i < participants.size(); i++)
	{
		participants[i]->ordersComplete = false;
		participants[i]->clearNegotiate();
		participants[i]->setDrawn(false);
		participants[i]->clearOrders();
		reinf.push_back(participants[i]->getReinF());
		attack.push_back(participants[i]->toAttack(m, reinf[i]));
		defend.push_back(participants[i]->toDefend(m, reinf[i]));
	}
	do {
		playersDone = participants.size();
		for (int i = 0; i < participants.size(); i++)
		{
			if (participants[i]->ordersComplete)
			{
				participants[i]->issueOrder(reinf[i], m, attack[i], defend[i], participants[i], deck, i);
			}
			else
			{
				playersDone--;
			}
		}
	} while (playersDone != 0);
	//TODO make the order making sequence
}

void executeOrderPhase(Map m, vector<Player*>& participants)
{
	int j = 0;
	int maxSize = 0;
	while (true)
	{
		for (int i = 0; i < participants.size(); i++)
		{
			maxSize = 0;
			if (j < participants[i]->getOrders().size())
			{
				(participants[i]->getOrders())[j]->execute();
				//since the orders are kept on the heap i remove the object here directly
				delete (participants[i]->getOrders())[j];
			}
			else
			{
				maxSize++;
			}
		}
		j++;
		if (maxSize >= participants.size())
		{
			break;
		}
	}
	for (int i = 0; i < participants.size(); i++)
	{
		//removing dangling pointers
		participants[i]->clearOrders();
	}
	//removing any empty players (can be done better with lamda functions but that will come later)
	for (int i = 0; i < participants.size(); i++)
	{
		if (participants[i]->getTerritories().size() == 0)
		{
			participants.erase(participants.begin() + i);
			i--;
		}
	}
	//move back to the start.. althought his can be handles by the gameloop
}
#pragma endregion
