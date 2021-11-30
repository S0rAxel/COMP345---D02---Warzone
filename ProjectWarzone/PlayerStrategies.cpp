#include "PlayerStrategies.h"
#include <iostream>

HumanPlayer::HumanPlayer() 
{

}

HumanPlayer::HumanPlayer(const HumanPlayer& hPlayer) 
{
	this->player = hPlayer.player;
}

HumanPlayer& HumanPlayer::operator=(const HumanPlayer& hPlayer) 
{
	// self-assignment guard
	if (this == &hPlayer)
		return *this;

	this->player = hPlayer.player;

	return *this;
}

void HumanPlayer::issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, int counter, Player* neutral)
{
	//reinf orders
	while (reinf > 0) {
		cout << "Reinforcement phase. You have " << me->getReinF() << " reinforcements to deploy. Please enter which territory to reinforce and how many to deploy." << endl;
		cout << "Here is a list of territory by their ID which you own:" << endl;
		for (int i = 0; i < me->getTerritories().size(); i++) {
			cout << me->getTerritories()[i]->getID() << endl;
		}
		int reinfToDeploy;
		int territoryID;
		territory* territory;
		cout << "Enter the territory ID:";
		cin >> territoryID;
		if (territoryID >= m.getTerritories().size() || territoryID < 0) {
			cout << "Territory does not exist. Please try again." << endl;
			continue;
		}
		territory = m.getTerritory(territoryID);
		cout << "Enter reinforcements to deploy:";
		cin >> reinfToDeploy;
		if (reinfToDeploy <= 0)
		{
			cout << "Invalid number of reinforcements. Please try again" << endl;
			continue;
		}
		reinf -= reinfToDeploy;
		if ( reinf >= 0)
		{
			me->addOrder(new Deploy(reinfToDeploy, me, territory));
		}
		else {
			reinf += reinfToDeploy;
			cout << "Attempted to deploy too many reinforcements. Retry" << endl;
		}
		
	}

	//card orders
	while (!me->havePlayedCard && me->getHand()->size() > 0) {
		string ans = "";
		cout << "You have cards available to play: " << me->getHand() << "would you like to play a card? y/n: ";
		cin >> ans;
		if (ans == "y" || ans == "Y") {
			int index;
			cout << "Enter which card you wish to play (enter the index): ";
			cin >> index;
			if (index < 0 || index > me->getHand()->size()) {
				cout << "Bad index. Try again." << endl;
				continue;
			}
			switch (me->getHand()->getCards()[index]->getCardType())
			{
			case (Card::bomb):
				me->addOrder(new Bomb(me, attack[counter - defend.size()]));
				break;
			case (Card::reinforcement):
				me->addReinF(5);
				break;
			case (Card::blockade):
				me->addOrder(new Blockade(me, neutral, defend[counter]));
				break;
			case (Card::airlift):
				//at the moment the planes are only good enough for 5 ppl
				me->addOrder(new Airlift(5, me, defend[0], attack[counter - defend.size()]));
				break;
			case (Card::diplomacy):
				me->addOrder(new Negotiate(me, attack[counter - defend.size()]->getOwner()));
				break;
			case (Card::EMPTY):
				break;
			}
			//removes card form hand
			(me->getHand()->getCards())[index]->play(index);
			me->havePlayedCard = true;
		}
		else if (ans == "n" || ans == "N") {
			cout << "Skipping cards. " << endl;
			break;
		}
		else {
			cout << "Bad answer. Please answer \"y\" or \"n\"." << endl;
		}
	}

	//advance orders
	{
		cout << "You may now issue advance orders. Enter \"-1\" anytime to stop issuing more advance orders." << endl;
		while (true) {
			int armies;
			int territoryID;
			territory* sTerritory;
			territory* tTerritory;
			cout << "Here is a list of territory by their ID which you own:" << endl;
			for (int i = 0; i < me->getTerritories().size(); i++) {
				cout << me->getTerritories()[i]->getID() << endl;
			}
			cout << "Enter the source territory ID: " << endl;
			cin >> territoryID;
			if (territoryID == -1) {
				cout << "Ending orders." << endl;
				break;
			}
			if (territoryID >= m.getTerritories().size() || territoryID < 0) {
				cout << "Territory does not exist. Please try again." << endl;
				continue;
			}
			sTerritory = m.getTerritory(territoryID);

			cout << "Enter the target territory ID: " << endl;
			cin >> territoryID;
			if (territoryID == -1) {
				cout << "Ending orders." << endl;
				break;
			}
			if (territoryID >= m.getTerritories().size() || territoryID < 0) {
				cout << "Territory does not exist. Please try again." << endl;
				continue;
			}
			tTerritory = m.getTerritory(territoryID);

			cout << "Enter the number of armies to advance with." << endl;
			cin >> armies;
			if (armies == -1) {
				cout << "Ending orders." << endl;
				break;
			}
			if (armies <= 0)
			{
				cout << "Invalid number of armies. Please try again" << endl;
				continue;
			}
			me->addOrder(new Advance(armies, me, sTerritory, tTerritory, deck));
		}
	}


}

vector<territory*> HumanPlayer::toAttack(Player* p, Map m)
{
	//decided by a human during issueORder().
	return vector<territory*>();
}

vector<territory*> HumanPlayer::toDefend(Player* p, Map m)
{
	//decided by a human blahblah
	return vector<territory*>();
}

AgressivePlayer::AgressivePlayer()
{

}

AgressivePlayer::AgressivePlayer(const AgressivePlayer& aPlayer)
{
	this->player = aPlayer.player;
}

AgressivePlayer& AgressivePlayer::operator=(const AgressivePlayer& aPlayer)
{
	// self-assignment guard
	if (this == &aPlayer)
		return *this;

	this->player = aPlayer.player;

	return *this;
}

void AgressivePlayer::issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, int counter, Player* neutral)
{
	//reinf
	territory* strongest = defend[0];
	me->addOrder(new Deploy(reinf, me, strongest));
	territory* bombprio = attack[0];

	for (int i = 0; i < attack.size(); i++) {
		if (attack[i]->getArmies() > bombprio->getArmies()) {
			bombprio = attack[i];
		}
	}

	//cards, bomb only
	if (!me->havePlayedCard) {
		for (int i = 0; i < me->getHand()->size(); i++) {
			if (me->getHand()->getCards()[i]->getCardType() == Card::bomb) {
				me->addOrder(new Bomb(me, bombprio));
			}
		}
	}

	//defend advance
	//TODO

	//attack advance
	//split attack equally with bordering territories. Remainder to strongest enemy territory.
	int totalArmies = strongest->getArmies() + reinf;
	int remainder = totalArmies % attack.size();
	for (int i = 0; i < attack.size(); i++) {
		me->addOrder(new Advance(totalArmies / attack.size(), me, strongest, attack[i], deck));
	}
	me->addOrder(new Advance(remainder, me, strongest, bombprio, deck));
}

vector<territory*> AgressivePlayer::toAttack(Player* p, Map m)
{
	//returns all bordering territories to the strongest territory
	territory* strongest = toDefend(p, m)[0];
	vector<territory*> attack;
	for (int i = 0; i < m.getTerritories().size(); i++) {
		if (strongest->isAdjacentTerritory(&m.getTerritories()[i]) && m.getTerritories()[i].getOwner() != p) {
			attack.push_back(&m.getTerritories()[i]);
		}
	}
	return attack;
}

vector<territory*> AgressivePlayer::toDefend(Player* p, Map m)
{
	//returns the player's single strongest territory
	vector<territory*> territories = p->getTerritories();
	territory* strongest = territories[0];
	for (int i = 0; i < territories.size(); i++) {
		int armies = territories[i]->getArmies();
		if (armies > strongest->getArmies()) {
			strongest = territories[i];
		}
	}
	vector<territory*> defend;
	defend.push_back(strongest);
	return defend;
}

BenevolentPlayer::BenevolentPlayer()
{

}

BenevolentPlayer::BenevolentPlayer(const BenevolentPlayer& bPlayer)
{
	this->player = bPlayer.player;
}

BenevolentPlayer& BenevolentPlayer::operator=(const BenevolentPlayer& bPlayer)
{
	// self-assignment guard
	if (this == &bPlayer)
		return *this;

	this->player = bPlayer.player;

	return *this;
}

void BenevolentPlayer::issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, int counter, Player* neutral)
{

}

vector<territory*> BenevolentPlayer::toAttack(Player* p, Map m)
{

}

vector<territory*> BenevolentPlayer::toDefend(Player* p, Map m)
{

}

NeutralPlayer::NeutralPlayer()
{

}

NeutralPlayer::NeutralPlayer(const NeutralPlayer& nPlayer)
{
	this->player = nPlayer.player;
}

NeutralPlayer& NeutralPlayer::operator=(const NeutralPlayer& nPlayer)
{
	// self-assignment guard
	if (this == &nPlayer)
		return *this;

	this->player = nPlayer.player;

	return *this;
}

void NeutralPlayer::issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, int counter, Player* neutral)
{

}

vector<territory*> NeutralPlayer::toAttack(Player* p, Map m)
{

}

vector<territory*> NeutralPlayer::toDefend(Player* p, Map m)
{

}

CheaterPlayer::CheaterPlayer()
{

}

CheaterPlayer::CheaterPlayer(const CheaterPlayer& cPlayer)
{
	this->player = cPlayer.player;
}

CheaterPlayer& CheaterPlayer::operator=(const CheaterPlayer& cPlayer)
{
	// self-assignment guard
	if (this == &cPlayer)
		return *this;

	this->player = cPlayer.player;

	return *this;
}

void CheaterPlayer::issueOrder(int& reinf, Map m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, int counter, Player* neutral)
{

}

vector<territory*> CheaterPlayer::toAttack(Player* p, Map m)
{

}

vector<territory*> CheaterPlayer::toDefend(Player* p, Map m)
{

}