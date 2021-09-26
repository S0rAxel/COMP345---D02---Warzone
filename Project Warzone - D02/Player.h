#pragma once

#include <string>
#include <list>
#include <iostream>
using namespace std;

class Player
{
public:
	Player() {

	}

	Player(const Player& player) {

	}

	~Player() {
		delete this;
	}

	Player& operator= (const Player& player) {

	}

	friend ostream& operator<<(ostream& stream, const Player& player);

private:
	list<int> countries;

public:
	string playerName;
	list<Order> orderList;

	list<int> toDefend();
	list<int> toAttack();
	void issueOrder();
};

ostream& operator<<(ostream& stream, const Player& player) {
	stream << "Player: " << player.playerName << endl;
	return stream;
}

class Order {
public:
	Order(string order) {
		this->order = order;
	}

public:
	string order;

	void executeOrder();
};
