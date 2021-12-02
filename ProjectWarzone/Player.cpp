#include <algorithm>
#include "Player.h"

Player::Player(string playerName)
{
	this->playerName = playerName;
	playOrder = -1;
	hand = new Hand();
}

Player::~Player()
{
	//delete hand;
	//delete playOrder;
}

Player& Player::operator=(const Player& player) {
	return *this;
}

vector<territory*> Player::toDefend(Map m)
{
	return strat->toDefend(m);
}

vector<territory*> Player::toAttack(Map m) {
	return strat->toAttack(m);
}

void Player::issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants)
{
	strat->issueOrder(reinf, m, attack, defend, me, deck, neutral, participants);
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

int Player::getTerritorySize()
{
	return territories.size();
}

int Player::getPlayOrder()
{
	return playOrder;
}

void Player::setPlayOrder(int playOrder)
{
	this->playOrder = playOrder;
}

void Player::setReinF(int numOfReinF)
{
	this->numOfReinF = numOfReinF;
}

vector<Player> Player::players;