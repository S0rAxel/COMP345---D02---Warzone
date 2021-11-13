#include "GameEngine.cpp"

void runGameLoop(vector<Player*>* players, Deck* deck)
{
	Map map = readfile("test.txt");
	vector<Player*> participants;
	for (int i = 0; i < players->size(); i++)
	{
		participants.push_back(players->operator[](i));
	}
	for (int i = 0; i < participants.size(); i++)
	{
		for (int j = 0; j < participants[i]->getTerritories().size(); j++)
		{
			map.getTerritory((participants[i]->getTerritories()[j])->getID())->setOwner(participants[i]);
		}
	}
	mainGameLoop(map, participants, deck);
}