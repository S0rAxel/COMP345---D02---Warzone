#include "Player.h"


Player& Player::operator=(const Player& player) {
	return *this;
}

list<Territory*> Player::toDefend() {
	list<Territory*> territoriesToDefend;

	// Creating and adding arbitrary territories to defend
	territoriesToDefend.push_back(new Territory("Gondor"));
	territoriesToDefend.push_back(new Territory("Rohan"));
	territoriesToDefend.push_back(new Territory("Shire"));

	cout << " List of Territories returned: " << endl;

	// Printing the territories to be returned for demo purposes
	for (Territory* territory : territoriesToDefend)
		cout << "\t - " << territory->name << endl;

	cout << endl;
	return territoriesToDefend;
}

list<Territory*> Player::toAttack() {
	list<Territory*> territoriesToAttack;

	// Creating and adding arbitrary territories to attack
	territoriesToAttack.push_back(new Territory("Mordor"));
	territoriesToAttack.push_back(new Territory("Isengard"));
	territoriesToAttack.push_back(new Territory("Shawdowland"));

	cout << " List of Territories returned: " << endl;

	// Printing the territories to be returned for demo purposes
	for (Territory* territory : territoriesToAttack)
		cout << "\t - " << territory->name << endl;

	cout << endl;
	return territoriesToAttack;
}

void Player::issueOrder() {
	Order* order = new Order();
	cout << " order was added to order list.\n" << endl;

	// Adding an empty order the the order list
	orders.push_back(order);
}

std::ostream& operator<<(std::ostream& stream, const Player& player) {
	return stream << " " << player.playerName;
}
