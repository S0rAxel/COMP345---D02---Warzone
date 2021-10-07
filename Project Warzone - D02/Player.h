#pragma once
#include <string>
#include <list>
#include <iostream>
using namespace std;

#pragma region Extra Classes

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


class Player
{
public:
	Player() { cout << " USED player();" << endl; };
	// Constructor with name to differentiate the different players during the demo
	Player(string name) : playerName(name) { cout << " USED player(string name);" << endl; };

	Player(const Player& otherPlayer) {
		playerName = otherPlayer.playerName;
		hand = otherPlayer.hand;
		territories = otherPlayer.territories;
		orders = otherPlayer.orders;
	};

	~Player() { delete this; }

	Player& operator= (const Player& player);

	friend ostream& operator <<(ostream& stream, const Player& player);

	list<Territory*> toDefend();
	list<Territory*> toAttack();
	void issueOrder();

private:
	list<Card*> hand;
	list<Territory*> territories;
	list<Order*> orders;

public:
	string playerName;
};