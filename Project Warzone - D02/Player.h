#pragma once
#include <string>
#include <list>
#include <iostream>
using namespace std;

#pragma region Extra Classes

class Order
{
public:
	Order(string order) { this->order = order; }

public:
	string order;

	void executeOrder();
};


class Territory
{
public:
	Territory(string name) : name(name) { }

	string name;
};

class Card
{

};

#pragma endregion


class Player
{
public:
	Player() { cout << " USED player();" << endl; };
	Player(string playerName);
	Player(const Player& player) { cout << " USED player(player &reference)" << endl; };

	~Player() { delete this; }

	Player& operator= (const Player& player);

	friend ostream& operator <<(ostream& stream, const Player& player);

	list<Territory*> toDefend();
	list<Territory*> toAttack();
	void issueOrder();

private:
	//Card hand[5] = { Card(), Card(), Card(), Card(), Card() };
	list<Territory*> territories;
	list<Order*> orders;

public:
	string playerName;
};