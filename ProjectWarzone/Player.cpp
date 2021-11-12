#include "Player.h"

Player& Player::operator=(const Player& player) {
	return *this;
}

vector<territory*> Player::toDefend(Map m) {
	vector<territory*> territoriesToDefend;
	//make randomizer for the to defend generating
	return territoriesToDefend;
}

vector<territory*> Player::toAttack(Map m) {
	vector<territory*> territoriesToAttack;
	//make randomizer for the to attack generating
	return territoriesToAttack;
}

void Player::issueOrder(int reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck) 
{
	if (reinf > 0)
	{
		//reinfordement logic
		addOrder(new Deploy(1, me, defend[0]));
	}
	else if(!havePlayedCard && hand->size()!=0)
	{
		//play a card and remove it from hand
		//must make the card making an order or apropriate type
		Player neutral;
		switch ((hand->getCards())[0]->getCardType())
		{
		case (0):
			addOrder(new Bomb(me, attack[0]));
			break;
		case (1):
			addReinF(5);
			break;
		case (2):
			addOrder(new Blockade(me, &neutral, defend[0]));
			break;
		case (3):
			addOrder(new Airlift(1, me, defend[0], attack[0]));
			break;
		case (4):
			addOrder(new Negotiate(me, attack[0]->getOwner()));
			break;
		}

		//removes card form hand
		(hand->getCards())[0]->play(0);
		havePlayedCard = true;
	}
	else
	{
		addOrder(new Advance(1, me, defend[0], attack[0], deck));
		//move logic
	}
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
