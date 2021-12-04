#include "GameEngine.h"
#include <vector>
#include "Cards.h"
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "MapDriver.h"
#include <fstream>

using namespace Engine;
using namespace std;

//Start the program with the current state pointer at null.
GameState* GameState::current = nullptr;
GameState** GameState::states = nullptr;

void GameState::SwitchState(GameState& newState) {
	GameState::current->Exit();
	GameState::current = &newState;
	GameState::current->Setup();

	//Workaround around to log the transition due to static method
	ofstream file("gamelog.txt", ios::app);
	file << "GameState::SwitchState(): State Changed to " << current->name << endl;
	file.close();
}

using namespace States;

void GameState::GameSetup() {
	cout << "Game Setup...\n\tInitializing states...\n";

	//Initialize all game states.
	GameState::states = new GameState * [8]{
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
	states[0]->links = { states[1], states[4] };
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
		delete* (GameState::states + i);
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
Start::Start() : GameState("Start", { "loadmap", "tournament" }) { }
LoadMap::LoadMap() : GameState("Loaded Map", { "loadmap", "validatemap" }) { }
ValidMap::ValidMap() : GameState("Validated Map", { "addplayer" }) { }
AddPlayers::AddPlayers() : GameState("Add Players", { "addplayer", "gamestart" }) { }
AssignReinf::AssignReinf() : GameState("Assign Reinforcements", { "issueorder" }) { }
IssueOrders::IssueOrders() : GameState("Issue Orders", { "issueorder", "endissueorders" }) { }
ExecOrders::ExecOrders() : GameState("Execute Orders", { "execorder", "endexecorders", "win" }) { }
GameOver::GameOver() : GameState("Win", { "replay", "quit" }) { }

//Again, there are no destructors for the derived
//classes since they define no members (see header file).

#pragma endregion

#pragma region State Behavior

//Base class stream insertion operator.
ostream& Engine::operator<<(ostream& out, GameState& state) {
	out << endl << state.name << " state.\nCommands: " << state.cmdList();
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

#pragma region Subject and ILoggable
void GameState::Attach(Observer* obs)
{
	Subject::Attach(obs);
}

void GameState::Detach(Observer* obs)
{
	Subject::Detach(obs);
}

void GameState::Notify(ILoggable& log)
{
	Subject::Notify(log);
}

string GameState::StringToLog()
{
	return "GameState::SwitchState(): State Changed to " + current->name + "\n";
}

#pragma endregion

//These will allow for custom behavior for every state on transition.
//Nothing for now.

void Start::Setup() { }
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

Map GameState::loadmapCmd(string filename)
{
	cout << "\nLoading map " << filename << "...\n";

	Map map = readfile(filename);

	return map;
}

bool GameState::validatemapCmd(Map map)
{
	cout << "\nValidating map " << map.getName() <<"...\n";
	if (validate(map))
		return true;
	else
		return false;
}

void GameState::addplayerCmd(string playerName)
{
	cout << "\nAdding player " << playerName <<"...\n";

	cout << "You can add between 2 and 6 players to the game" << endl;
	cout << "Adding player " << (Player::players.size() + 1) << "..." << endl;
	Player player = Player(playerName);
	Player::players.push_back(player);
}

void GameState::gamestartCmd(Map* map, Deck* deck)
{
	cout << "\nPerforming game setup..." << endl;

	// Distributing the territories to the players
	int numOfTerrPerPlayer = map->getNumOfTerr() / Player::players.size();
	int remainderOfTerrs = map->getNumOfTerr() - (numOfTerrPerPlayer * Player::players.size());

	// This gives territories to the players but it's possible that there are still some unallocated territories
	// This happens if the remainder is not zero
	// At most, a player may have 1 territory more than another player
	// Note however that this is still quite fair since maps have a lot of territories (which means players have many territories overall as well)
	for (int i = 0; i < Player::players.size(); i++)
		for (int j = 0; j < numOfTerrPerPlayer; j++)
			Player::players.at(i).addTerritories(map->getTerritory(j + i*numOfTerrPerPlayer));

	for (Player player : Player::players)
	{
		cout << player << " territories: " << player.getTerritories().size() << endl;
	}

	if (remainderOfTerrs != 0)
	{
		for (int i = 0; i < remainderOfTerrs; i++)
			Player::players.at(i).addTerritories(map->getTerritory((numOfTerrPerPlayer * Player::players.size()) + i));
	}
	//linking the territories back to the players
	for (int i = Player::players.size()-1; i >= 0; i--)
	{
		for (int j = 0; j < Player::players[i].getTerritories().size(); j++)
		{
			Player::players[i].getTerritories()[j]->setOwner(&Player::players[i]);
		}
	}

	// Randomly determining the order of play
	srand((unsigned int)time(NULL));

	// We first start by generating random numbers
	vector<int> nums;
	for (int i = 0; i < Player::players.size(); i++)
	{
		nums.push_back(rand());
	}

	// Then we can determine the actual play order from those random numbers
	for (int i = 0; i < Player::players.size(); i++)
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

		Player::players.at(indexOfMax).setPlayOrder(i + 1);
		nums.at(indexOfMax) = -1;
	}

	// Give 50 armies to each player
	for (int i = 0; i < Player::players.size(); i++)
		Player::players.at(i).setReinF(50);

	// Each player draws two cards
	for (int i = 0; i < Player::players.size(); i++)
		deck->draw(Player::players.at(i).getHand());
}

void tournamentLoop(vector<Map>& mapRotation, int numGames, int turnLimit) {
	//Play 'numGames' games for each map in 'mapRotation'.
	for (Map map : mapRotation) {
		for (int i = 0; i < numGames; i++) {
			//Make a copy of the static deck as not to modify it.
			Deck* deckCopy = new Deck(Card::deck);
			//Do setup and play the game until winner or draw.
			GameState::gamestartCmd(&map, deckCopy);
			mainGameLoop(&map, deckCopy, turnLimit);
		}
	}
}

void mainGameLoop(Map* map, Deck* deck, int turnLimit)
{
	//Copy all current players, put them in a new vector. 
	//This new vector can be modified without at will without fear of altering the static player vector.
	vector<Player*> participants;
	for (int i = 0; i < Player::players.size(); i++)
	{
		participants.push_back(&Player::players[i]);
	}

	for (Player* player : participants)
	{
		cout << *player << " territories: " << player->getTerritories().size() << endl;
	}


	//This player doesn't participate in the turn order, it simply acts as a holder for hidden territories where 'blockade' is used.
	Player* blockadeManager = new Player();
	int turnCounter = 0;

	bool ended = reinforcementPhase(map, participants);
	while (!ended)
	{
		cout << "  -- Turn " << turnCounter << " --  " << endl;

		//removing empty player if there is one
		//needs to be the manipulatable vector as to not change the actual players
		for (int i = 0; i < participants.size(); i++)
		{
			if (participants[i]->getTerritories().size() == 0)
			{
				participants.erase(participants.begin() + i);
			}
		}
		issueOrderPhase(map, participants, deck, blockadeManager);
		executeOrderPhase(map, participants);
		ended = reinforcementPhase(map, participants);

		//Stop game if reached turn limit.
		//A max turn count of anything less than zero makes this never trigger.
		if (++turnCounter == turnLimit) {
			cout << "\n\nThe game reached the turn limit (" << turnLimit << ") without a winner.\nThe game is declared as a draw!" << endl;
			return;
		}
	}
	cout << "player " << participants[0]->getName() << " won congrats game Over" << endl;
}


bool reinforcementPhase(Map* m, vector<Player*> participants)
{
	Player* tempOwner;
	//loop for all players to give players appropriate reinforcements base on territories owned / 3
	for (int i = 0; i < participants.size(); i++)
	{
		participants[i]->addReinF((participants[i]->getTerritories().size()) / 3);
		cout << participants[i]->getName() << " recieved " << (participants[i]->getTerritories().size()) / 3 << " troops form their " << participants[i]->getTerritories().size() << " territories owned" << endl;
	}
	//to get the continent bonus
	for (int i = 0; i < m->getNumOfCont(); i++)
	{
		//tempOwner = m->getTerritory(m->getContinent(i)->getTerrID(0))->getOwner();
		bool getBonus = false;
		for (int j = 1; j < m->getContinent(i)->getLength(); j++)
		{
			if (m->getTerritory(m->getContinent(i)->getTerrID(j))->getOwner() != m->getTerritory(m->getContinent(i)->getTerrID(0))->getOwner())
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
			m->getTerritory(m->getContinent(i)->getTerrID(0))->getOwner()->addReinF(m->getContinent(i)->getBonus());
			cout << "continent bonus for continent " << i <<", " << m->getContinent(i)->getBonus() << " has been assignet to player " << m->getTerritory(m->getContinent(i)->getTerrID(0))->getOwner()->getName() << "." << endl;
		}
	}
	//cheking if only one player remains and if that one player owns all the territories
	if (participants.size() == 1 && participants[0]->getTerritories().size() == m->getNumOfTerr())
	{
		return true;
	}
	else
	{
		return false;
	}

}

void issueOrderPhase(Map* m, vector<Player*> participants, Deck* deck, Player* neutral)
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
		defend.push_back(participants[i]->toDefend(m));
		attack.push_back(participants[i]->toAttack(m));

	}
	do {
		playersDone = participants.size();
		for (int i = 0; i < participants.size(); i++)
		{
			if (!participants[i]->ordersComplete)
			{
				participants[i]->issueOrder(reinf[i], m, attack[i], defend[i], participants[i], deck, neutral, participants);
			}
			else
			{
				playersDone--;
			}
		}
	} while (playersDone != 0);
	//TODO make the order making sequence
}

void executeOrderPhase(Map* m, vector<Player*> participants)
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
			cout << "player " << participants[i]->getName() << "has been eliminated" << endl;
		}
	}
	//move back to the start.. althought his can be handles by the gameloop
}