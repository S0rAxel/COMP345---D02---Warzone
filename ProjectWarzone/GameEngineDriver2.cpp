#include "GameEngine.h"
#include "Player.h"
#include "Cards.h"
#include "GameEngineDriver2.h"
#include "MainGameLoop.cpp"

using namespace Engine;

void startupPhaseDemo()
{
    vector<Player*>* players = new vector<Player*>();

	Card::ctype bomb = Card::bomb;
	Card::ctype reinforcement = Card::reinforcement;
	Card::ctype blockade = Card::blockade;
	Card::ctype airlift = Card::airlift;
	Card::ctype diplomacy = Card::diplomacy;

	Deck* deck = new Deck();

	deck->addCard(new Card(bomb));
	deck->addCard(new Card(blockade));
	deck->addCard(new Card(airlift));
	deck->addCard(new Card(reinforcement));
	deck->addCard(new Card(diplomacy));
	deck->addCard(new Card(bomb));
	deck->addCard(new Card(reinforcement));
	deck->addCard(new Card(airlift));
	deck->addCard(new Card(airlift));
	deck->addCard(new Card(diplomacy));
	deck->addCard(new Card(diplomacy));
	deck->addCard(new Card(diplomacy));

	GameState* mainState;
	mainState->startupPhase(players, deck);

	cout << "Verifying that the information has been correctly added..." << endl;
	for (int i = 0; i < players->size(); i++)
	{
		cout << "Information of player " << (i + 1) << "..." << endl;
		cout << "PlayOrder is " << *players->at(i)->getPlayOrder() << endl;
		cout << "Reinforcements are " << players->at(i)->getReinF() << endl;
		cout << "Number of territories is " << players->at(i)->getTerritorySize() << endl;

		cout << endl;
	}
	runGameLoop(players, deck);
}
