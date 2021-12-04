#include "PlayerStrategies.h"
#include <iostream>
#include "Player.h"

HumanPlayer::HumanPlayer()
{

}

HumanPlayer::HumanPlayer(Player& player)
{
	this->player = &player;
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

	delete player;
	player = new Player(*hPlayer.player);

	return *this;
}

void HumanPlayer::issueOrder(int& reinf, Map* m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants)
{
	cout << ">> HumanPlayer::issueOrder()" << endl;
	//create reinf orders by input
	while (reinf > 0) {
		cout << "Reinforcement phase. You have " << reinf << " reinforcements to deploy. Please enter which territory to reinforce and how many to deploy." << endl;
		cout << "Here is a list of territory by their ID which you own:" << endl;
		for (int i = 0; i < me->getTerritories().size(); i++) {
			cout << me->getTerritories()[i]->getID() << endl;
		}
		int reinfToDeploy;
		int territoryID;
		territory* territory;
		cout << "Enter the territory ID:";
		cin >> territoryID;
		if (territoryID >= m->getTerritories().size() || territoryID < 0) {
			cout << "Territory does not exist. Please try again." << endl;
			continue;
		}
		territory = m->getTerritory(territoryID);
		cout << "Enter reinforcements to deploy:";
		cin >> reinfToDeploy;
		if (reinfToDeploy <= 0)
		{
			cout << "Invalid number of reinforcements. Please try again" << endl;
			continue;
		}
		reinf -= reinfToDeploy;
		if (reinf >= 0)
		{
			me->addOrder(new Deploy(reinfToDeploy, me, territory));
		}
		else {
			reinf += reinfToDeploy;
			cout << "Attempted to deploy too many reinforcements. Retry" << endl;
		}

	}

	//create card orders
	while (!me->havePlayedCard && me->getHand()->size() > 0) {
		string ans = "";
		cout << "You have cards available to play: " << *me->getHand() << "would you like to play a card? y/n: ";
		cin >> ans;
		if (ans == "y" || ans == "Y") {
			int index;
			cout << "Enter which card you wish to play (enter the index): ";
			cin >> index;
			if (index < 0 || index > me->getHand()->size()) {
				cout << "Bad index. Try again." << endl;
				continue;
			}
			bool invalid = false;
			switch (me->getHand()->getCards()[index]->getCardType())
			{
			case (Card::bomb):
			{
				cout << "Playing bomb card. Enter target territory ID: ";
				int id;
				cin >> id;
				if (id >= m->getTerritories().size() || id < 0) {
					cout << "Territory does not exist. Please try again." << endl;
					invalid = true;
					break;
				}
				me->addOrder(new Bomb(me, m->getTerritory(id)));
				break;
			}
			case (Card::reinforcement):
				cout << "Playing reinforcment card." << endl;
				me->addReinF(5);
				break;
			case (Card::blockade):
			{
				cout << "Playing blockade card. Enter target territory ID: ";
				int id;
				cin >> id;
				if (id >= m->getTerritories().size() || id < 0) {
					cout << "Territory does not exist. Please try again." << endl;
					invalid = true;
					break;
				}
				me->addOrder(new Blockade(me, neutral, m->getTerritory(id)));
				break;
			}
			case (Card::airlift):
			{
				cout << "Playing airlift card. Enter source territory ID: ";
				int id, id2, armies;
				cin >> id;
				if (id >= m->getTerritories().size() || id < 0) {
					cout << "Territory does not exist. Please try again." << endl;
					invalid = true;
					break;
				}
				cout << "Enter target territory ID: ";
				cin >> id2;
				if (id2 >= m->getTerritories().size() || id2 < 0) {
					cout << "Territory does not exist. Please try again." << endl;
					invalid = true;
					break;
				}
				cout << "Enter number of armies to airlift: ";
				cin >> armies;
				if (armies <= 0)
				{
					cout << "Invalid number of armies. Please try again" << endl;
					invalid = true;
					break;
				}
				me->addOrder(new Airlift(armies, me, m->getTerritory(id), m->getTerritory(id2)));
				break;
			}
			case (Card::diplomacy):
			{
				cout << "Playing negotiate card. Enter target player name: ";
				string name;
				cin >> name;
				Player* target = NULL;
				for (int i = 0; i < participants.size(); i++) {
					if (participants[i]->getName() == name) {
						target = participants[i];
					}
				}
				if (target == NULL) {
					cout << "Player does not exist. Please try again." << endl;
					invalid = true;
					break;
				}
				me->addOrder(new Negotiate(me, target));
				break;
			}
			case (Card::EMPTY):
				break;
			}
			//removes card form hand
			if (!invalid) {
				(me->getHand()->getCards())[index]->play(index);
				me->havePlayedCard = true;
				break;
			}

		}
		else if (ans == "n" || ans == "N") {
			cout << "Skipping cards. " << endl;
			break;
		}
		else {
			cout << "Bad answer. Please answer \"y\" or \"n\"." << endl;
		}
	}
	//create advance orders

	cout << "You may now issue advance orders. Enter \"-1\" anytime to stop issuing more advance orders." << endl;
	while (true)
	{
		int armies;
		int territoryID;
		territory* sTerritory;
		territory* tTerritory;

		cout << "Territories you own: " << me->getTerritories().size() << " | List of territories by their ID : " << endl;

		for (int i = 0; i < me->getTerritories().size(); i++)
		{
			cout << me->getTerritories()[i]->getID() << endl;
		}

		cout << "\nEnter the source territory ID: " << endl;
		cin >> territoryID;
		if (territoryID == -1) {
			cout << "Ending orders." << endl;
			break;
		}
		if (territoryID >= m->getTerritories().size() || territoryID < 0) {
			cout << "Territory does not exist. Please try again." << endl;
			continue;
		}
		sTerritory = m->getTerritory(territoryID);

		cout << "Enter the target territory ID: " << endl;
		cin >> territoryID;
		if (territoryID == -1) {
			cout << "Ending orders." << endl;
			break;
		}
		if (territoryID >= m->getTerritories().size() || territoryID < 0) {
			cout << "Territory does not exist. Please try again." << endl;
			continue;
		}
		tTerritory = m->getTerritory(territoryID);

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

	me->ordersComplete = true;
}

vector<territory*> HumanPlayer::toAttack(Player* me, Map* m)
{
	cout << ">> HumanPlayer::toAttack()" << endl;
	//decided by a human during issueORder().
	return vector<territory*>();
}

vector<territory*> HumanPlayer::toDefend(Player* me, Map* m)
{
	cout << ">> HumanPlayer::toDefend()" << endl;
	//decided by a human during issueOrder().
	return vector<territory*>();
}

AggressivePlayer::AggressivePlayer()
{

}

AggressivePlayer::AggressivePlayer(Player& player)
{
	this->player = &player;
}

AggressivePlayer::AggressivePlayer(const AggressivePlayer& aPlayer)
{
	this->player = aPlayer.player;
}

AggressivePlayer& AggressivePlayer::operator=(const AggressivePlayer& aPlayer)
{
	// self-assignment guard
	if (this == &aPlayer)
		return *this;

	delete player;
	player = new Player(*aPlayer.player);

	return *this;
}

void AggressivePlayer::issueOrder(int& reinf, Map* m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants)
{
	cout << ">> AggressivePlayer::issueOrder()" << endl;

	cout << attack.size() << endl;
	cout << defend.size() << endl;

	//reinf, just reinforces its strongest territory
	territory* strongest = defend[0];
	me->addOrder(new Deploy(reinf, me, strongest));
	territory* bombprio = NULL;
	if (attack.size() > 0) {
		bombprio = attack[0];

		//find strongest enemy territory adjacent to strongest owned territory to bomb and dump remainder armies
		for (int i = 0; i < attack.size(); i++) {
			if (attack[i]->getArmies() > bombprio->getArmies()) {
				bombprio = attack[i];
			}
		}

		//bomb card
		if (!me->havePlayedCard && me->getHand()->size() > 0) {
			for (int i = 0; i < me->getHand()->size(); i++) {
				if (me->getHand()->getCards()[i]->getCardType() == Card::bomb) {
					me->addOrder(new Bomb(me, bombprio));
					me->getHand()->getCards()[i]->play(i);
					me->havePlayedCard = true;
				}
			}
		}
	}
	

	//cards, will prioritize bombing, then reinforcing. Will never play diplomatic or airlift.
	if (!me->havePlayedCard && me->getHand()->size() > 0) {
		
		for (int i = 0; i < me->getHand()->size(); i++) {
			if (me->getHand()->getCards()[i]->getCardType() == Card::reinforcement) {
				me->addReinF(5);
				me->havePlayedCard = true;
			}
		}
		
	}

	//defend strongest territory
	for (int i = 0; i < me->getTerritories().size(); i++) {
		if (me->getTerritories()[i]->isAdjacentTerritory(strongest) && me->getTerritories()[i]->getArmies() > 0) {
			//moves all armies adjacent to strongest onto strongest
			me->addOrder(new Advance(me->getTerritories()[i]->getArmies(), me, me->getTerritories()[i], strongest, deck));
		}
	}

	//attack advance
	//split attack equally with bordering territories. Remainder to strongest enemy territory regardless of bombed or not.
	if (attack.size() > 1)
	{
		int totalArmies = strongest->getArmies() + reinf;
		int remainder = totalArmies % attack.size();
		for (int i = 0; i < attack.size(); i++) {
			me->addOrder(new Advance(totalArmies / attack.size(), me, strongest, attack[i], deck));
		}

			me->addOrder(new Advance(remainder, me, strongest, bombprio, deck));
	}

	me->ordersComplete = true;
}

vector<territory*> AggressivePlayer::toAttack(Player* me, Map* m)
{
	cout << ">> AggressivePlayer::toAttack()" << endl;

	//returns all bordering territories to the strongest territory
	territory* strongest = toDefend(me, m)[0];
	
	vector<territory*> attack;
	if (strongest != nullptr)
	{
		for (int i = 0; i < m->getTerritories().size(); i++) {
			if (strongest->isAdjacentTerritory(&m->getTerritories()[i]) && m->getTerritories()[i].getOwner() != me) {
				attack.push_back(&m->getTerritories()[i]);
			}
		}

	}
	cout << ">> AggressivePlayer::toAttack(): Territories to Attack = " << attack.size() << endl;

	return attack;
}

vector<territory*> AggressivePlayer::toDefend(Player* me, Map* m)
{
	cout << ">> AggressivePlayer::toDefend()" << endl;

	vector<territory*> defend;
	//defend.push_back(new territory(2, "Canada", 1));
	//returns the player's single strongest territory
	if (me->getTerritories().size() > 0)
	{
		vector<territory*> territories = me->getTerritories();
		territory* strongest = territories[0];
		for (int i = 0; i < territories.size(); i++) {
			int armies = territories[i]->getArmies();
			if (armies > strongest->getArmies()) {
				strongest = territories[i];
			}
		}

		defend.push_back(strongest);

	}
	cout << ">> AggressivePlayer::toDefend(): Territories to Defend = " << defend.size() << endl;

	return defend;
}

BenevolentPlayer::BenevolentPlayer()
{

}

BenevolentPlayer::BenevolentPlayer(Player& player)
{
	this->player = &player;
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

	delete player;
	player = new Player(*bPlayer.player);

	return *this;
}

void BenevolentPlayer::issueOrder(int& reinf, Map* m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants)
{
	cout << ">> BenevolentPlayer::issueOrder()" << endl;

	//reinforces weakest territory or multiple equally weak territories
	int remainder = reinf % defend.size();
	for (int i = 0; i < defend.size(); i++) {
		me->addOrder(new Deploy(reinf / defend.size(), me, defend[i]));
	}
	me->addOrder(new Deploy(remainder, me, defend[0]));

	//cards, will prioritize playing diplomacy with every player, then reinforce card. Will never bomb or airlift.
	if (!me->havePlayedCard && me->getHand()->size() > 0) {
		for (int i = 0; i < me->getHand()->size(); i++) {
			if (me->getHand()->getCards()[i]->getCardType() == Card::diplomacy) {
				for (int j = 0; j < participants.size(); j++) {
					if (!participants[j]->isNegotiate(me)) {
						me->addOrder(new Negotiate(me, participants[j]));
						me->getHand()->getCards()[i]->play(i);
						me->havePlayedCard = true;
					}
				}
			}
		}
		if (!me->havePlayedCard) {
			for (int i = 0; i < me->getHand()->size(); i++) {
				if (me->getHand()->getCards()[i]->getCardType() == Card::reinforcement) {
					me->addReinF(5);
					me->getHand()->getCards()[i]->play(i);
					me->havePlayedCard = true;
				}
			}
		}
	}

	//does not attack anyone
	me->ordersComplete = true;
}

vector<territory*> BenevolentPlayer::toAttack(Player* me, Map* m)
{
	//attacks no one.
	cout << ">> BenevolentPlayer::toAttack()" << endl;

	cout << ">> BenevolentPlayer::toAttack(): Territories to Attack = 0" << endl;

	return vector<territory*>();
}

vector<territory*> BenevolentPlayer::toDefend(Player* me, Map* m)
{
	cout << ">> BenevolentPlayer::toDefend()" << endl;

	vector<territory*> defend;

	//weakest territories
	if (me->getTerritories().size() > 0)
	{
		territory* weakest = me->getTerritories()[0];

		for (int i = 0; i < me->getTerritories().size(); i++) {
			if (weakest->getArmies() > me->getTerritories()[i]->getArmies()) {
				weakest = me->getTerritories()[i];
			}
		}
		defend.push_back(weakest);
		for (int i = 0; i < me->getTerritories().size(); i++) {
			if (weakest->getArmies() == me->getTerritories()[i]->getArmies()) {
				defend.push_back(me->getTerritories()[i]);
			}
		}
	}

	cout << ">> BenevolentPlayer::toDefend(): Territories to Defend = " << defend.size() << endl;
	return defend;
}

NeutralPlayer::NeutralPlayer()
{

}

NeutralPlayer::NeutralPlayer(Player& player)
{
	this->player = &player;
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

	delete player;
	player = new Player(*nPlayer.player);

	return *this;
}

void NeutralPlayer::issueOrder(int& reinf, Map* m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants)
{
	//does nothing ¯\_(ツ)_/¯
	cout << ">> NeutralPlayer::issueOrder()" << endl;
	cout << ">> He does nothing..." << endl;
	me->ordersComplete = true;
}

vector<territory*> NeutralPlayer::toAttack(Player* me, Map* m)
{
	//attacks no one.
	cout << ">> NeutralPlayer::toAttack()" << endl;

	return vector<territory*>();
}

vector<territory*> NeutralPlayer::toDefend(Player* me, Map* m)
{
	cout << ">> NeutralPlayer::toDefend()" << endl;

	//me->setStrategy(new AggressivePlayer());

	//cout << ">> NeutralPlayer has become an AggressivePlayer" << endl;

	return vector<territory*>();
}

CheaterPlayer::CheaterPlayer()
{

}

CheaterPlayer::CheaterPlayer(Player& player)
{
	this->player = &player;
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

	delete player;
	player = new Player(*cPlayer.player);

	return *this;
}

void CheaterPlayer::issueOrder(int& reinf, Map* m, vector<territory*> attack, vector<territory*> defend, Player* me, Deck* deck, Player* neutral, vector<Player*> participants)
{
	cout << ">> CheaterPlayer::issueOrder()" << endl;

	//reinforce territories
	me->addOrder(new Deploy(reinf, me, me->getTerritories()[0]));

	//Sends conquer order to all adjacent territories
	for (int i = 0; i < attack.size(); i++) {
		me->addOrder(new Conquer(me, attack[i]));
	}
	me->ordersComplete = true;
}

vector<territory*> CheaterPlayer::toAttack(Player* me, Map* m)
{
	cout << ">> CheaterPlayer::toAttack()" << endl;

	//all adjacent territories
	vector<territory*> attack;

	if (me->getTerritories().size() > 0)
	{
		for (int i = 0; i < me->getTerritories().size(); i++) {
			for (int j = 0; j < m->getTerritories().size(); j++) {
				if (me->getTerritories()[i]->isAdjacentTerritory(m->getTerritory(j))) {
					bool inAttack = false;
					for (int k = 0; k < attack.size(); k++) {
						if (m->getTerritory(j) == attack[k]) {
							inAttack = true;
							break;
						}
					}
					if (!inAttack) {
						attack.push_back(m->getTerritory(j));
					}
				}
			}
		}
	}

	cout << ">> CheaterPlayer::toAttack(): Territories to Attack: " << attack.size() << endl;

	return attack;
}

vector<territory*> CheaterPlayer::toDefend(Player* me, Map* m)
{
	cout << ">> CheaterPlayer::toDefend()" << endl;
	//defends nothing.
	cout << ">> CheaterPlayer::toDefend(): Does not defend" << endl;

	return vector<territory*>();
}