#include "CommandProcessing.h"
#include "GameEngine.h"
#include "Map.h"
#include "Drivers.h"

Map readfile(string);

int main()
{
	// TODO fix log observer stuff

	Engine::GameState::GameSetup();

	system("pause");

	CommandProcessor::startup();
	Command* cmd;
	Command* followUp;
	string cmdEffect;

	Map loadedMap;

	Card::ctype bomb = Card::bomb;
	Card::ctype reinforcement = Card::reinforcement;
	Card::ctype blockade = Card::blockade;
	Card::ctype airlift = Card::airlift;
	Card::ctype diplomacy = Card::diplomacy;

	// TODO possibly have the deck as a static member of the Deck class
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

	int nextStateIndex;
	do {
		cmd = CommandProcessor::current->getCommand();
		//cmd->Attach(&obs);
		cmdEffect = "";

		//Special command, exits. For demo only.
		if (*cmd == "$abort") {
			break;
		}
		//Special command, prints log of processor. For demo only.
		else if (*cmd == "$log") {
			CommandProcessor::current->printLog();
			cmdEffect = "Printed log of command processor.";
		}
		else {
			//Check the validity of the command.
			nextStateIndex = CommandProcessor::validate(*cmd);

			//If the state index isn't -1, switches to the state received by 'validate()'.
			if (nextStateIndex >= 0) {

				//If 'quit' was valid, then terminate the control flow.
				if (*cmd == "quit") {
					break;
				}
				else if (*cmd == "loadmap") {
					cout << "\nEnter the map's file name:";

					followUp = CommandProcessor::current->getCommand();
					//followUp->Attach(&obs);
					followUp->saveEffect("Follow-up of last command.");

					// Executing the loadmap command
					loadedMap = Engine::GameState::loadmapCmd(followUp->value);

					//Record and print command effect.
					cmdEffect += "Loaded map file: " + followUp->value + ".\n";
					cout << "Loaded map file: " << followUp->value << endl;
				}
				else if (*cmd == "validatemap") {
					// Executing the validatemap command
					bool isMapValid = Engine::GameState::validatemapCmd(loadedMap);

					//Record and print command effect.
					if (isMapValid)
					{
						cmdEffect += "The map was valid.\n";
						cout << "The map was valid." << endl;
					}
					else
					{
						cmdEffect += "The map was invalid.\n";
						cout << "The map was invalid." << endl;
					}
				}
				else if (*cmd == "addplayer") {

					// TODO doesn't perfectly work yet
					if (Player::players.size() >= 6)
					{
						cout << "You have added the maximum amount of players. Please execute the gamestart command." << endl;
						break;
					}

					cout << "\nEnter the player's name";

					followUp = CommandProcessor::current->getCommand();
					followUp->saveEffect("Follow-up of last command.");

					// Executing the addplayer command
					Engine::GameState::addplayerCmd(followUp->value);

					cmdEffect += "Added player " + followUp->value + ".\n";
					cout << "Added player " + followUp->value << endl;
				}
				else if (*cmd == "gamestart") {
					// Executing the gamestart command
					Engine::GameState::gamestartCmd(loadedMap, deck);

					cmdEffect += "Gamestart command executed.\n";
					cout << "Gamestart command executed." << endl;

					// TEMP debug code
					cout << "Verifying that the information has been correctly added..." << endl;
					for (int i = 0; i < Player::players.size(); i++)
					{
						cout << "Information of player " << (i + 1) << "..." << endl;
						cout << "PlayOrder is " << Player::players.at(i).getPlayOrder() << endl;
						cout << "Reinforcements are " << Player::players.at(i).getReinF() << endl;
						cout << "Number of territories is " << Player::players.at(i).getTerritorySize() << endl;

						cout << endl;
					}
				}
				//adding the main game loop comands
				vector<Player*> participants;
				for (int i = 0; i < Player::players.size(); i++)
				{
					participants.push_back(&Player::players[i]);
				}
				mainGameLoop(loadedMap, participants, deck);
				Engine::GameState::SwitchState(*Engine::GameState::current->links.at(nextStateIndex));
				cmdEffect += "Switched to other state using '" + cmd->value + "'.";
			}
			else {
				cmdEffect = "None. Command was invalid.";
				cout << "Invalid Command.\n\n";
			}
		}

		//Saves the effect of the command.
		cmd->saveEffect(cmdEffect);
	} while (true);


	delete CommandProcessor::current;

	Engine::GameState::GameExit();

}

/*#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <fstream>
#include "LoggingObserver.h"
#include "GameEngineDriver2.h"
#include "Drivers.h"

using namespace std;

int main()
{

	cout << "\n\t - WARZONE PROJECT - \n";

	ofstream file("gamelog.txt", ios::app);

	time_t t = time(0);

	file << "\n - New log created at time: " << ctime(&t) << " \n" << endl;

	file.close();

	LogObserver* lObs = new LogObserver();
	vector<Player*>* players = new vector<Player*>;
	Deck* deck = new Deck();


	CommandProcessingDemo(*lObs);
	OrderExecutionDriverDemo(*lObs);
	startupPhaseDemo(*lObs);
	ObserverDriver(*lObs);
}*/
