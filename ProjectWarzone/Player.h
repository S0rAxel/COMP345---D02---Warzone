#pragma once

#include <string>
#include <list>
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

	list<territory*> getTerritories() { return territories; }

	list<territory*> toDefend();
	list<territory*> toAttack();
	Hand* getHand() { return hand; }
	void issueOrder();

private:
	list<territory*> territories;
	Hand* hand;
	list<Order*> orders;

public:
	string playerName;
};