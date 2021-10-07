#include <iostream>
#include "Player.h"
#include "PlayerDriver.h"

using namespace std;

list<Player*> playerList;

void PlayerDriverDemo()
{
	cout << " - WARZONE PROJECT | PLAYER DRIVER TESTER -\n" << endl;

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