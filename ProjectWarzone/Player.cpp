#include "Player.h"

Player::Player(string playerName)
{
	this->playerName = playerName;
	playOrder = new int(-1);
	hand = new Hand();
}

Player& Player::operator=(const Player& player) {
	return *this;
}

vector<territory*> Player::toDefend(Map m) 
{
	vector<territory*> territoriesToDefend;
	//TLDR the player assigns a random number of territories to defend
	for (int i = 0; i < rand() % (getTerritories().size() - 1, 1); i++)
	{
		territoriesToDefend.push_back(getTerritories()[rand() % (getTerritories().size())]);
	}
	//make randomizer for the to defend generating
	return territoriesToDefend;
}

vector<territory*> Player::toAttack(Map m) {
	vector<territory*> territoriesToAttack;
	territory *temp;
	int limit = rand() % (territories.size()/2);
	int counter = 0;
	int i = 0;
	while (counter < limit)
	{
		temp = getTerritories()[rand() % (getTerritories().size())];
		for (int i = 0; i < temp->getNumOfBorders(); i++);
		{
			if (m.getTerritory(temp->getBorderID(i))->getOwner()->getName() != getName())
			{
				territoriesToAttack.push_back(temp);
				break;
			}
		}
		counter++;
	}
	//make randomizer for the to attack generating
	return territoriesToAttack;
}

void Player::issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, int counter, Player* neutral) 
{
	bool goOn = false;
	int armies = rand() % (reinf / 2 + 1) + (reinf / 2 + 1);
	reinf -= armies;
	//this first if is to ensure that the character doesn't
	if (ordersComplete)
	{
		return;
	}
	if (reinf > 0)
	{
		//reinfordement logic
		if (counter < defend.size())
		{
			addOrder(new Deploy(armies, me, defend[counter]));
		}
		else
		{
			addOrder(new Deploy(armies, me, m.getTerritory(attack[counter]->getBorderID(0))));
		}
	}
	else if(!havePlayedCard && getHand()->size()!=0)
	{
		//play a card and remove it from hand
		//must make the card making an order or apropriate type
		switch ((getHand()->getCards())[0]->getCardType())
		{
		case (Card::bomb):
			addOrder(new Bomb(me, attack[counter - defend.size()]));
			break;
		case (Card::reinforcement):
			addReinF(5);
			break;
		case (Card::blockade):
			addOrder(new Blockade(me, neutral, defend[counter]));
			break;
		case (Card::airlift):
			//at the moment the planes are only good enough for 5 ppl
			addOrder(new Airlift(5, me, defend[0], attack[counter - defend.size()]));
			break;
		case (Card::diplomacy):
			addOrder(new Negotiate(me, attack[counter - defend.size()]->getOwner()));
			break;
		case (Card::EMPTY):
			break;
		}
		//removes card form hand
		(hand->getCards())[0]->play(0);
		havePlayedCard = true;
	}
	else if (counter - defend.size() <= attack.size())
	{
		if (counter >= defend.size())
		{
			addOrder(new Advance(m.getTerritory(attack[counter - defend.size()]->getBorderID(0))->getArmies() - 1,
				me,
				m.getTerritory(attack[counter - defend.size()]->getBorderID(0)), 
				attack[counter - defend.size()], deck));
		}
		else
		{
			addOrder(new Advance(m.getTerritory(defend[counter]->getBorderID(0))->getArmies() - 1,
				me,
				m.getTerritory(defend[counter]->getBorderID(0)),
				defend[counter], deck));
		}
		//move logic
	}
	else
	{
		ordersComplete = true;
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

int Player::getTerritorySize()
{
	return territories.size();
}

int* Player::getPlayOrder()
{
	return playOrder;
}

void Player::setPlayOrder(int* playOrder)
{
	*this->playOrder = *playOrder;
}

void Player::setReinF(int numOfReinF)
{
	this->numOfReinF = numOfReinF;
}
