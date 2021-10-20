#include "Player.h"


Player& Player::operator=(const Player& player) {
	return *this;
}

list<territory*> Player::toDefend() {
	list<territory*> territoriesToDefend;

	return territoriesToDefend;
}

list<territory*> Player::toAttack() {
	list<territory*> territoriesToAttack;

	return territoriesToAttack;
}

void Player::issueOrder() {
	Order* order = new Order();
	
	orders.push_back(order);
}

std::ostream& operator<<(std::ostream& stream, const Player& player) {
	return stream << " " << player.playerName;
}
