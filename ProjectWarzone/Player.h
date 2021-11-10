#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

using namespace std;

/*#pragma region Extra Classes

//As is this is a temporary class is does not have the copy constructor, nor the stream or assignment operators
class Territory
{
public:
	Territory(string name) : name(name) { }

	string name;
};

//As is this is a temporary class is does not have the copy constructor, nor the stream or assignment operators
class Order { };

//As is this is a temporary class is does not have the copy constructor, nor the stream or assignment operators
class Card { };

#pragma endregion
*/

class Card;
class Order;
class territory;

class Player
{
public:
	Player() {};
	
	Player(string name) : playerName(name) {};

	Player(const Player& otherPlayer) {
		playerName = otherPlayer.playerName;
		hand = otherPlayer.hand;
		territories = otherPlayer.territories;
		orders = otherPlayer.orders;
	};

	~Player() { delete this; }

	Player& operator= (const Player& player);

	friend ostream& operator <<(ostream& stream, const Player& player);

	vector<territory*> getTerritories() { return territories; }

	vector<territory*> toDefend();
	vector<territory*> toAttack();
	Hand* getHand() { return hand; }
	void issueOrder();
	vector<Order*> getOrders();
	int getReinF() { return numOfReinF; }
	void addReinF(int reinf) { numOfReinF += reinf; }
	void removeReinf(int reinf) { numOfReinF -= reinf; }//must add a validation before using this one
	vector<Player*> getNegotiate() { return negotiate; }
	void clearNegotiate() { negotiate.clear(); }
	void addNegotiate(Player* player) { negotiate.push_back(player); }
	bool isNegotiate(Player* player);

private:
	vector<territory*> territories;
	Hand* hand;
	vector<Order*> orders;
	int numOfReinF;
	vector<Player*> negotiate; //vector of players that cannot be attacked. Clear after every turn

public:
	string playerName;
};