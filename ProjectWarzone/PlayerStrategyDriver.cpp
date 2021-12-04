#include <iostream>
#include <vector>
#include "Drivers.h"
#include "Player.h"
#include "PlayerStrategies.h"
#include "GameEngine.h"
#include "Cards.h"
#include "Map.h"
#include "MapDriver.h"

using namespace std;

void PrintPlayers();

Player* aggPlayer;
Player* neuPlayer;
Player* benPlayer;
Player* chePlayer;
Player* humPlayer;
Player* chaPlayer;

void PlayerStrategyDriver()
{
	cout << "\t - PLAYER STRATEGY DRIVER - " << endl;

	Map map = readfile("test.txt");

	if (validate(map))
		cout << "\n>> Map loading and validated... \n" << endl;
	else
	{
		cout << "- ERROR: Invalid MAP - " << endl;
		return;
	}

	aggPlayer = new Player("Aggresive");	// Aggresive player that will demonstrate that it will attack as much as it can.
	neuPlayer = new Player("Neutral");		// Neutral player that will demonstrate that it will not issue any order, but if attacked it will become aggresive.
	benPlayer = new Player("Benevolent");	// Benevolent player that will demonstrate that it will only defend its weakest territories and never attack.
	chePlayer = new Player("Cheater");		// Cheater player that will demonstrate it can take territories once per turn.
	humPlayer = new Player("Human");		// Human player that will demonstrate that he can intake input from user.
	chaPlayer = new Player("Random");		// Player that will change strategies througout the demo.

	aggPlayer->setStrategy(new AggressivePlayer(aggPlayer));
	neuPlayer->setStrategy(new NeutralPlayer(neuPlayer));
	benPlayer->setStrategy(new BenevolentPlayer(benPlayer));
	chePlayer->setStrategy(new CheaterPlayer(chePlayer));
	humPlayer->setStrategy(new HumanPlayer(humPlayer));
	chaPlayer->setStrategy(new BenevolentPlayer(chaPlayer)); // Setting the changing player to benevolent 

	// Adding the players to the static vector
	Player::players.push_back(*aggPlayer);
	Player::players.push_back(*neuPlayer);
	Player::players.push_back(*benPlayer);
	Player::players.push_back(*chePlayer);
	Player::players.push_back(*humPlayer);
	Player::players.push_back(*chaPlayer);

	Card::ctype bomb = Card::bomb;
	Card::ctype reinforcement = Card::reinforcement;
	Card::ctype blockade = Card::blockade;
	Card::ctype airlift = Card::airlift;
	Card::ctype diplomacy = Card::diplomacy;

	// Instantiating a deck
	Deck* deck = new Deck();

	// Adding different cards to the Deck
	deck->addCard(new Card(bomb));
	deck->addCard(new Card(blockade));
	deck->addCard(new Card(airlift));
	deck->addCard(new Card(reinforcement));
	deck->addCard(new Card(diplomacy));
	deck->addCard(new Card(bomb));
	deck->addCard(new Card(reinforcement));
	deck->addCard(new Card(airlift));
	deck->addCard(new Card(airlift));
	deck->addCard(new Card(diplomacy));
	deck->addCard(new Card(diplomacy));
	deck->addCard(new Card(diplomacy));
	
	// Printing all players, showing their name, the strategy class they are implementing and the type they belong to. It should always display player, as they are all players.
	PrintPlayers();

	Engine::GameState::gamestartCmd(map, deck);

	mainGameLoop(map, deck, 100);

	//Remove the added players for rest of demo.
	Player::players.clear();
}

void PrintPlayers()
{
	// Printing each one individually as some take specific indententation so it is easy to look at.
	cout << ">> Name:" << *chaPlayer << "\t\t| Strat: " << typeid(*chaPlayer->getStrategy()).name() << "\t| Type: " << typeid(*chaPlayer).name() << endl;
	cout << ">> Name:" << *aggPlayer << "\t| Strat: " << typeid(*aggPlayer->getStrategy()).name() << "\t| Type: " << typeid(*aggPlayer).name() << endl;
	cout << ">> Name:" << *neuPlayer << "\t| Strat: " << typeid(*neuPlayer->getStrategy()).name() << "\t| Type: " << typeid(*neuPlayer).name() << endl;
	cout << ">> Name:" << *benPlayer << "\t| Strat: " << typeid(*benPlayer->getStrategy()).name() << "\t| Type: " << typeid(*benPlayer).name() << endl;
	cout << ">> Name:" << *chePlayer << "\t| Strat: " << typeid(*chePlayer->getStrategy()).name() << "\t| Type: " << typeid(*chePlayer).name() << endl;
	cout << ">> Name:" << *humPlayer << "\t\t| Strat: " << typeid(*humPlayer->getStrategy()).name() << "\t| Type: " << typeid(*humPlayer).name() << endl;
}

/*#include <iostream>
#include "Player.h"

using namespace std;

list<Player*> playerList;

void PlayerDriverDemo()
{
	// Creating  first player
	cout << " Creating new player" << endl;
	Player* player1 = new Player("Player1");
	cout << *player1 << " was created...\n" << endl;
	
	// Adding player to the list for demo purposes
	playerList.push_back(player1);

	// Creating second player
	cout << " Creating new player" << endl;
	Player* player2 = new Player("Player2");
	cout << *player2 << " was created...\n" << endl;

	system("pause");

	// Adding second player to the list for demo purposes
	playerList.push_back(player2);

	// Looping through the players to show functionality
	for (Player* player : playerList)
	{
		cout << *player << " will issue an order..." << endl;
		player->issueOrder();

		cout << *player << " will attack: " << endl;
		player->toAttack();

		cout << *player << " will defend: " << endl;
		player->toDefend();
	}
	cout << endl;
}

/*void Menu()
{
	int selection = 0;

	do {

		cout << " - Select an option: \n\t(1). Add Player\n\t(2). See all Player \n\t(3). Issue Order \n\t(4). Quit\n Option: ";
		cin >> selection;
		if (selection <= 0 || selection > 4)
		{
			cout << "\n ERROR: Option does not exist or is not a number\n" << endl;
		}
	} while (selection <= 0 || selection > 4);

	switch (selection)
	{
	case 1:
		AddPlayer();
		break;
	case 2:
		SeeAllPlayer();
		break;
	case 3:
		IssueOrder();
		break;
	case 4:
		return;
		break;
	}

	Menu();
}

inline void AddPlayer()
{
	string playerName;
	cout << "\n - ADDING A PLAYER -\n" << endl;
	cout << " Name of the new Player: ";
	cin >> playerName;

	Player* player = new Player(playerName);

	cout << "\n\n new " << *player << endl;

	players.push_back(player);
}

void SeeAllPlayer()
{
	if (players.empty())
	{
		cout << "\n THERE ARE NO PLAYERS\n" << endl;
		return;
	}

	cout << " All Players:" << endl;

	for (Player* player : players)
	{
		cout << "\t - " << *player << endl;
	}

	cout << endl;
	system("pause");
	cout << endl;
}

void IssueOrder()
{
	cout << "\nISSUING AN ORDER\n" << endl;

	cout << "List of Players:\n" << endl;

	if (players.empty()) { cout << "\n THERE IS NO PLAYERS \n" << endl; return; }

	int i = 0;
	for (Player* player : players)
	{
		cout << "\t[" << ++i << "] " << *player << endl;
	}

	int selection = 0;

	do 
	{
		cout << "\n Choose a player to issue order: ";
		cin >> selection;
		if (selection <= 0 || selection > players.size())
		{
			cout << "\n ERROR: Option does not exist or is not a number\n" << endl;
		}
	} while (selection <= 0 || selection > players.size());

	counter = next(players.begin(), selection);
	cout << *counter;

	cout << endl;
	system("pause");
	cout << endl;
}*/ 