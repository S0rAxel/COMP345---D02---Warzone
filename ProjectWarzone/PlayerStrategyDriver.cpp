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

	aggPlayer = new Player("Aggressive");	// Aggresive player that will demonstrate that it will attack as much as it can.
	neuPlayer = new Player("Neutral");		// Neutral player that will demonstrate that it will not issue any order, but if attacked it will become aggresive.
	benPlayer = new Player("Benevolent");	// Benevolent player that will demonstrate that it will only defend its weakest territories and never attack.
	chePlayer = new Player("Cheater");		// Cheater player that will demonstrate it can take territories once per turn.
	humPlayer = new Player("Human");		// Human player that will demonstrate that he can intake input from user.
	chaPlayer = new Player("Random");		// Player that will change strategies througout the demo.

	// Adding the players to the static vector
	Player::players.push_back(*humPlayer);
	Player::players.push_back(*aggPlayer);
	Player::players.push_back(*neuPlayer);
	Player::players.push_back(*chePlayer);
	Player::players.push_back(*benPlayer);
	Player::players.push_back(*chaPlayer);

	for (size_t i = 0; i < Player::players.size(); i++)
	{
		if (Player::players[i].getName() == "Aggressive")
		{
			Player::players[i].setStrategy(new AggressivePlayer(Player::players[i]));
		}
		else if (Player::players[i].getName() == "Neutral")
		{
			Player::players[i].setStrategy(new NeutralPlayer(Player::players[i]));
		}
		else if (Player::players[i].getName() == "Benevolent")
		{
			Player::players[i].setStrategy(new BenevolentPlayer(Player::players[i]));
		}
		else if (Player::players[i].getName() == "Cheater")
		{
			Player::players[i].setStrategy(new CheaterPlayer(Player::players[i]));
		}
		else if (Player::players[i].getName() == "Human")
		{
			Player::players[i].setStrategy(new HumanPlayer(Player::players[i]));
		}
		else if (Player::players[i].getName() == "Random")
		{
			Player::players[i].setStrategy(new AggressivePlayer(Player::players[i])); // Setting the changing player to Aggressive 
		}
	}

	// Instantiating a deck
	Deck* deck = new Deck();

	// Adding different cards to the Deck
	deck->addCard(new Card(Card::bomb));
	deck->addCard(new Card(Card::airlift));
	deck->addCard(new Card(Card::diplomacy));
	deck->addCard(new Card(Card::reinforcement));
	deck->addCard(new Card(Card::blockade));
	deck->addCard(new Card(Card::airlift));
	deck->addCard(new Card(Card::bomb));
	deck->addCard(new Card(Card::diplomacy));
	deck->addCard(new Card(Card::reinforcement));
	deck->addCard(new Card(Card::airlift));
	deck->addCard(new Card(Card::diplomacy));

	// Printing all players, showing their name, the strategy class they are implementing and the type they belong to. It should always display player, as they are all players.
	PrintPlayers();

	cout << "\n>> Random player Changes from Aggressive to Cheater player\n" << endl;
	for (size_t i = 0; i < Player::players.size(); i++)
	{
		if (Player::players[i].getName() == "Random")
		{
			Player::players[i].setStrategy(new CheaterPlayer(Player::players[i]));
		}
	}

	cout << ">> Printing again all players..." << endl;

	PrintPlayers();

	Engine::GameState::gamestartCmd(&map, deck);
	mainGameLoop(&map, deck, 3);

	//Remove the added players for rest of demo.
	Player::players.clear();
}


void PrintPlayers()
{
	for (size_t i = 0; i < Player::players.size(); i++)
	{
		if (Player::players[i].getName() == "Human" || Player::players[i].getName() == "Random")
		{
			cout << ">> Name:" << Player::players[i] << "\t\t| Strat: " << typeid(*Player::players[i].getStrategy()).name() << "\t| Type: " << typeid(Player::players[i]).name() << endl;
		}
		else
		{
			cout << ">> Name:" << Player::players[i] << "\t| Strat: " << typeid(*Player::players[i].getStrategy()).name() << "\t| Type: " << typeid(Player::players[i]).name() << endl;
		}
	}
}
