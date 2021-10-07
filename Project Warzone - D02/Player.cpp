#include "Player.h"


Player::Player(string playerName) : playerName(playerName) {
	cout << " USED player(string name);" << endl;
}

Player& Player::operator=(const Player& player) {
	return *this;
}

list<Territory*> Player::toDefend() {
	list<Territory*> territoriesToDefend;

	territoriesToDefend.push_back(new Territory("Gondor"));
	territoriesToDefend.push_back(new Territory("Rohan"));
	territoriesToDefend.push_back(new Territory("Shire"));


	for (Territory* territory : territoriesToDefend)
		cout << " territory: " << territory->name << endl;

	return territoriesToDefend;
}

list<Territory*> Player::toAttack() {
	list<Territory*> territoriesToAttack;

	territoriesToAttack.push_back(new Territory("Mordor"));
	territoriesToAttack.push_back(new Territory("Isengard"));
	territoriesToAttack.push_back(new Territory("Minas Morgul"));

	for (Territory* territory: territoriesToAttack)
		cout << " territory: " << territory->name << endl;

	return territoriesToAttack;
}

void Player::issueOrder() {
	cout << playerName << " is issuing an order" << endl;

	Order* order = new Order("Attack");
	orders.push_back(order);
}

std::ostream& operator<<(std::ostream& stream, const Player& player) {
	return stream << "Player: " << player.playerName;
}

void Order::executeOrder() {
	cout << " Order executing: " << order << endl;
}
