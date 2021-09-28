#include "Player.h"


Player::Player(string playerName) : playerName(playerName) {
	cout << " USED player(string name);" << endl;
}

Player& Player::operator=(const Player& player) {
	return *this;
}

list<string> Player::toDefend() {
	list<string> territoriesToDefend;

	territoriesToDefend.push_back("Gondor");
	territoriesToDefend.push_back("Rohan");
	territoriesToDefend.push_back("Shire");

	return territoriesToDefend;
}

list<string> Player::toAttack() {
	list<string> territoriesToAttack;

	territoriesToAttack.push_back("Mordor");
	territoriesToAttack.push_back("Isengard");
	territoriesToAttack.push_back("Minas Morgul");

	return territoriesToAttack;
}

void Player::issueOrder() {
	cout << playerName << " is issuing an order" << endl;
	Order order("Attack");
	int selection = 0;
	cout << " - Select the order you want to give \n\t1. Attack\n\t2. Defend ";

	orderList.push_back(order);
}

std::ostream& operator<<(std::ostream& stream, const Player& player) {
	return stream << "Player: " << player.playerName;
}

void Order::executeOrder() {
	cout << " Order executing: " << order << endl;
}
