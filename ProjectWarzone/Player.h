#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include "PlayerStrategies.h"

using namespace std;

/*#pragma region Extra Classes

//As is this is a temporary class is does not have the copy constructor, nor the stream or assignment operators
class Territory
{
public:
	Territory(string name) : name(name) { }

	string name;
};

//As is this is a temporary class is does not have the copy constructor, nor the stream or assignment operators
class Order { };

//As is this is a temporary class is does not have the copy constructor, nor the stream or assignment operators
class Card { };

#pragma endregion
*/

class Card;
class Order;
class territory;

class Player
{
public:

	static vector<Player> players;

	Player() {};
	
	Player(string name);

	Player(string name, Hand* hand) { playerName = name; this->hand = hand; };

	Player(const Player& otherPlayer) {
		playerName = otherPlayer.playerName;
		hand = otherPlayer.hand;
		territories = otherPlayer.territories;
		orders = otherPlayer.orders;
	};

	~Player();

	string getName() { return playerName; }

	Player& operator= (const Player& player);

	friend ostream& operator <<(ostream& stream, const Player& player);

	vector<territory*> getTerritories() { return territories; }
	void addTerritories(territory* territory) { territories.push_back(territory); }
	void removeTerritories(territory* territory);
	vector<territory*> toDefend(Map m);
	vector<territory*> toAttack(Map m);
	vector<territory*> toAttack(int ammount);
	vector<territory*> toDefend(int ammount);
	Hand* getHand() { return hand; }
	void issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, int counter, Player* neutral);
	void IssueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck);
	vector<Order*> getOrders();
	void addOrder(Order* o) { orders.push_back(o); }
	void removeOrder(Order* o);
	void clearOrders() { orders.clear(); }
	int getReinF() { return numOfReinF; }
	void setReinF(int numOfReinF);
	void addReinF(int reinf) { numOfReinF += reinf; }
	void removeReinf(int reinf) { numOfReinF -= reinf; }//must add a validation before using this one
	vector<Player*> getNegotiate() { return negotiate; }
	void setDrawn(bool drawn) { this->drawn = drawn; }
	bool getDrawn() { return drawn; }
	void clearNegotiate() { negotiate.clear(); }
	void addNegotiate(Player* player) { negotiate.push_back(player); }
	bool isNegotiate(Player* player);
	bool ordersComplete;
	bool havePlayedCard;
	void setHand(Hand* hand) { this->hand = hand; }
	PlayerStrategy* getStrategy() { return strat; }
	void setStrategy(PlayerStrategy* strat) { this->strat = strat; }

	int getTerritorySize();
	int getPlayOrder();
	void setPlayOrder(int playOrder);

private:
	vector<territory*> territories;
	Hand* hand;
	vector<Order*> orders;
	int numOfReinF;
	vector<Player*> negotiate; //vector of players that cannot be attacked. Clear after every turn
	bool drawn; //player has drawn card. Set to false after every turn
	PlayerStrategy* strat;
	int playOrder;

public:
	string playerName;
};