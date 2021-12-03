#pragma once
#include "Map.h"
#include "Cards.h"

class Player;

class PlayerStrategy
{
public:
	Player* player;
	virtual void issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants) = 0;
	virtual vector<territory*> toAttack(Map m) = 0;
	virtual vector<territory*> toDefend(Map m) = 0;
};

class HumanPlayer : public PlayerStrategy
{
public:
	HumanPlayer();
	HumanPlayer(Player* player);
	HumanPlayer(const HumanPlayer& hPlayer);

	HumanPlayer& operator= (const HumanPlayer& hPlayer);

	void issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants);
	vector<territory*> toAttack(Map m);
	vector<territory*> toDefend(Map m);
};

class AggressivePlayer : public PlayerStrategy
{
public:
	AggressivePlayer();
	AggressivePlayer(Player* player);
	AggressivePlayer(const AggressivePlayer& aPlayer);

	AggressivePlayer& operator= (const AggressivePlayer& aPlayer);

	void issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants);
	vector<territory*> toAttack(Map m);
	vector<territory*> toDefend(Map m);
};

class BenevolentPlayer : public PlayerStrategy
{
public:
	BenevolentPlayer();
	BenevolentPlayer(Player* player);
	BenevolentPlayer(const BenevolentPlayer& bPlayer);

	BenevolentPlayer& operator= (const BenevolentPlayer& bPlayer);

	void issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants);
	vector<territory*> toAttack(Map m);
	vector<territory*> toDefend(Map m);
};

class NeutralPlayer : public PlayerStrategy
{
public:
	NeutralPlayer();
	NeutralPlayer(Player* player);
	NeutralPlayer(const NeutralPlayer& nPlayer);

	NeutralPlayer& operator= (const NeutralPlayer& nPlayer);

	void issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants);
	vector<territory*> toAttack(Map m);
	vector<territory*> toDefend(Map m);
};

class CheaterPlayer : public PlayerStrategy
{
public:
	CheaterPlayer();
	CheaterPlayer(Player* player);
	CheaterPlayer(const CheaterPlayer& cPlayer);

	CheaterPlayer& operator= (const CheaterPlayer& cPlayer);

	void issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants);
	vector<territory*> toAttack(Map m);
	vector<territory*> toDefend(Map m);
};
