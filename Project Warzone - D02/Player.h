#pragma once

#include <string>
#include <list>
#include <iostream>
using namespace std;

class Order {
public:
	Order(string order) { this->order = order; }

public:
	string order;

	void executeOrder();
};

class Player
{
public:
	Player() { cout << " USED player();" << endl; };
	Player(string playerName);
	Player(const Player& player) { cout << " USED player(player &reference)" << endl; };

	~Player() { delete this; }

	Player& operator= (const Player& player);

	friend std::ostream& operator <<(std::ostream& stream, const Player& player);

	list<string> toDefend();
	list<string> toAttack();
	void issueOrder();

private:
	list<string> territories;
	list<Order> orderList;

public:
	string playerName;
};
