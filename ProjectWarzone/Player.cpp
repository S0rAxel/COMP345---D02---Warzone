#include "Player.h"

Player& Player::operator=(const Player& player) {
	return *this;
}

vector<territory*> Player::toDefend() {
	vector<territory*> territoriesToDefend;

	return territoriesToDefend;
}

vector<territory*> Player::toAttack() {
	vector<territory*> territoriesToAttack;

	return territoriesToAttack;
}

void Player::issueOrder() {
	//TODO MUST MAKE ORDER MAKING LOGIC
}

vector<Order*> Player::getOrders()
{
	return orders;
}

bool Player::isNegotiate(Player* player)
{
	std::vector<Player*>::iterator it = std::find(negotiate.begin(), negotiate.end(), player);
	if (it != negotiate.end())
	{
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& stream, const Player& player) {
	return stream << " " << player.playerName;
}

void Player::removeTerritories(territory* territory)
{
	for (int i = 0; i < territories.size(); i++)
	{
		if (territories[i] == territory)
		{
			territories.erase(territories.begin() + i);
			break;
		}
	}
}

void Player::removeOrder(Order* o)
{
	for (int i = 0; i < orders.size(); i++)
	{
		if (orders[i] == o)
		{
			orders.erase(orders.begin() + i);
			break;
		}
	}
}
