#pragma once

class Player;

class PlayerStrategy 
{
public:
	Player* player;
	virtual void issueOrder() = 0;
	virtual void toAttack() = 0;
	virtual void toDefend() = 0;
};

class HumanPlayer : public PlayerStrategy
{
public:
	HumanPlayer();
	HumanPlayer(const HumanPlayer& hPlayer);
	
	HumanPlayer& operator= (const HumanPlayer& hPlayer);

	void issueOrder();
	void toAttack();
	void toDefend();
};

class AgressivePlayer : public PlayerStrategy
{
public:
	AgressivePlayer();
	AgressivePlayer(const AgressivePlayer& aPlayer);

	AgressivePlayer& operator= (const AgressivePlayer& aPlayer);

	void issueOrder();
	void toAttack();
	void toDefend();
};


class BenevolentPlayer : public PlayerStrategy
{
public:
	BenevolentPlayer();
	BenevolentPlayer(const BenevolentPlayer& bPlayer);

	BenevolentPlayer& operator= (const BenevolentPlayer& bPlayer);

	void issueOrder();
	void toAttack();
	void toDefend();
};


class NeutralPlayer : public PlayerStrategy
{
public:
	NeutralPlayer();
	NeutralPlayer(const NeutralPlayer& nPlayer);

	 NeutralPlayer& operator= (const NeutralPlayer& nPlayer);

	void issueOrder();
	void toAttack();
	void toDefend();
};


class CheaterPlayer : public PlayerStrategy
{
public:
	CheaterPlayer();
	CheaterPlayer(const CheaterPlayer& cPlayer);

	CheaterPlayer& operator= (const CheaterPlayer& cPlayer);

	void issueOrder();
	void toAttack();
	void toDefend();
};
