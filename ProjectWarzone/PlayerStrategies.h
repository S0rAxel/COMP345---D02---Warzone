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
	HumanPlayer(const HumanPlayer& hPlayer);
	
	HumanPlayer& operator= (const HumanPlayer& hPlayer);

	void issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants);
	vector<territory*> toAttack(Player* p, Map m);
	vector<territory*> toDefend(Player* p, Map m);
};

class AgressivePlayer : public PlayerStrategy
{
public:
	AgressivePlayer();
	AgressivePlayer(const AgressivePlayer& aPlayer);

	AgressivePlayer& operator= (const AgressivePlayer& aPlayer);

	void issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants);
	vector<territory*> toAttack(Player* p, Map m);
	vector<territory*> toDefend(Player* p, Map m);
};


class BenevolentPlayer : public PlayerStrategy
{
public:
	BenevolentPlayer();
	BenevolentPlayer(const BenevolentPlayer& bPlayer);

	BenevolentPlayer& operator= (const BenevolentPlayer& bPlayer);

	void issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants);
	vector<territory*> toAttack(Player* p, Map m);
	vector<territory*> toDefend(Player* p, Map m);
};


class NeutralPlayer : public PlayerStrategy
{
public:
	NeutralPlayer();
	NeutralPlayer(const NeutralPlayer& nPlayer);

	 NeutralPlayer& operator= (const NeutralPlayer& nPlayer);

	void issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants);
	vector<territory*> toAttack(Player* p, Map m);
	vector<territory*> toDefend(Player* p, Map m);
};


class CheaterPlayer : public PlayerStrategy
{
public:
	CheaterPlayer();
	CheaterPlayer(const CheaterPlayer& cPlayer);

	CheaterPlayer& operator= (const CheaterPlayer& cPlayer);

	void issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants);
	vector<territory*> toAttack(Player* p, Map m);
	vector<territory*> toDefend(Player* p, Map m);
};
