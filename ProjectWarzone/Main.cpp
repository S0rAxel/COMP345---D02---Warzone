#include "CommandProcessing.h"
#include "GameEngine.h"
#include "Map.h"
#include "Drivers.h"

Map readfile(string);

int main()
{
	PlayerStrategyDriver();

	system("pause");
	// TODO fix log observer stuff

	Engine::GameState::GameSetup();

	system("pause");

	CommandProcessor::startup();
	Command* cmd;
	Command* followUp;
	string cmdEffect;

	vector<Map> loadedMaps;

	Card::ctype bomb = Card::bomb;
	Card::ctype reinforcement = Card::reinforcement;
	Card::ctype blockade = Card::blockade;
	Card::ctype airlift = Card::airlift;
	Card::ctype diplomacy = Card::diplomacy;

	//Create the card deck.
	Card::deck = Deck();
	Card::deck.addCard(new Card(bomb));
	Card::deck.addCard(new Card(blockade));
	Card::deck.addCard(new Card(airlift));
	Card::deck.addCard(new Card(reinforcement));
	Card::deck.addCard(new Card(diplomacy));
	Card::deck.addCard(new Card(bomb));
	Card::deck.addCard(new Card(reinforcement));
	Card::deck.addCard(new Card(airlift));
	Card::deck.addCard(new Card(airlift));
	Card::deck.addCard(new Card(diplomacy));
	Card::deck.addCard(new Card(diplomacy));
	Card::deck.addCard(new Card(diplomacy));

	int nextStateIndex;
	do {
		cmd = CommandProcessor::current->getCommand();
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
				//Keep track of if there were any error with the current command.
				bool noError = true;

				//If 'quit' was valid, then terminate the control flow.
				if (*cmd == "quit") {
					break;
				}

				else if (*cmd == "tournament") {
					int numOfGames;
					int numOfTurns;
					//Is used for both list of maps & player strategies to make sure not to many are passed.
					int amount;

					cout << "Commands: (-M) ";
					//Makes sure that first command is map breakpoint.
					noError = CommandProcessor::current->getCommand()->value == "-M";
					if (noError) cout << "\n-M Add name of MAP file (1 to 5)";

					//List of maps.
					amount = 0;
					while (noError) {
						followUp = CommandProcessor::current->getCommand();

						//Expected breakpoint to start listing player strategies.
						if (followUp->value == "-P") {
							if (amount < 1) {
								cout << "Provide at least 1 valid map.";
								noError = false;
							}
							else cout << "-P : Add Type of player (2 to 4) \nTypes to add (aggresive, neutral, cheater, human, benevolent)";
							break;
						}
						//Stop if too many maps are given.
						else if (++amount > 5) {
							cout << "Too many maps!";
							noError = false;
						}
						else {
							bool mapIsValid = true;
							cout << "Checking " << followUp->value << "...";
							try {
								loadedMaps.push_back(Engine::GameState::loadmapCmd(followUp->value));

								//Record and print command effect.
								if (Engine::GameState::validatemapCmd(loadedMaps.back())) {
									cout << "Loaded map " << followUp->value << " ..." << endl;
									cout << "Commands: (<Map file name>, -P)";
								}
								else {
									throw invalid_argument("Map is not valid.");
								}
							}
							catch (invalid_argument e) {
								cout << followUp->value << " is invalid." << endl;
								amount--;
							}
						}
					}

					//List of players.
					amount = 0;
					while (noError) {
						followUp = CommandProcessor::current->getCommand();

						//Expected breakpoint to give number of games.
						if (followUp->value == "-G") {
							if (amount < 2) {
								cout << "Provide at least 2 players.";
								noError = false;
							}
							else cout << "-G breakpoint.";
							break;
						}
						//Stops if too many players are given.
						else if (++amount > 4) {
							cout << "Too many players!";
							noError = false;
						}
						else {
							cout << "Commands: (<Type of player>, -G)" << endl;

							//Emulate switch staement as it doesn't work with strings.
							if (*followUp == "human") {
								//TODO: Add human player to players vector.
							}
							else if (*followUp == "benevolent") {
								//TODO: Add benevolent player to players vector.
							}
							else if (*followUp == "neutral") {
								//TODO: Add neutral player to players vector.
							}
							else if (*followUp == "aggressive") {
								//TODO: Add aggressive player to players vector.
							}
							else if (*followUp == "cheater") {
								//TODO: Add cheater player to players vector.
							}
							else {
								noError = false;
								cout << '\'' << followUp->value << "' is not a valid player strategy.";
							}

							if (noError) {
								cout << "Added " << followUp->value <<" player.";
							}
						}
					}

					//Number of games per map.
					if (noError) {
						followUp = CommandProcessor::current->getCommand();
						try {
							numOfGames = stoi(followUp->value);
							if (numOfGames < 1 || numOfGames > 5)
								throw invalid_argument("Number of games is too low / high.");
						}
						catch (invalid_argument err) {
							cout << "Invalid number of games per map.";
							noError = false;
						}
						if (noError) {
							cout << "Games per map: " << numOfGames;
							//Makes sure next command is max number of turn breakpoint.
							noError = CommandProcessor::current->getCommand()->value == "-D";
						}
					}

					//Max number of turns per game.
					if (noError) {
						cout << "-D breakpoint.";
						followUp = CommandProcessor::current->getCommand();
						try {
							numOfTurns = stoi(followUp->value);
							if (numOfTurns < 10 || numOfTurns > 50)
								throw invalid_argument("Max number of turns is too low / high.");
						}
						catch (invalid_argument err) {
							cout << "Invalid max number of turns per game.";
							noError = false;
						}
						if (noError)
							cout << "Turns per game: " << numOfTurns;
					}

					//Final validity check.
					if (noError) {
						cout << "\nStarting Tournament..." << endl;
						//Engine::GameState::current->SwitchState(*Engine::GameState::current->links.at(nextStateIndex));

						//Need to make a method to pass multiple maps that will call gamestartCmd.
						//torunamentCmd(loadedMaps, players, deck, numGames, maxTurns);
					}
					else {
						cout << "\nTournament command is invalid." << endl;
					}
				}
				else if (*cmd == "loadmap") {
					cout << "\nEnter the map's file name:";

					followUp = CommandProcessor::current->getCommand();
					followUp->saveEffect("Follow-up of last command.");

					// Executing the loadmap command
					try {
						loadedMaps.push_back(Engine::GameState::loadmapCmd(followUp->value));

						cout << "Loaded map: " << followUp->value << endl;
						//Record and print command effect.
						cmdEffect += "Loaded map file: " + followUp->value + ".\n";
					}
					catch(invalid_argument e) {
						noError = false;
						cmdEffect += "Map file: " + followUp->value + " was invalid.\n";
						cout << "Provided file is not a map.";
					}
				}
				else if (*cmd == "validatemap") {
					// Executing the validatemap command. Check if each map is correctly defined.
					for (Map map : loadedMaps) {
						if (Engine::GameState::validatemapCmd(map)) {
							cout << map.getName() << " is valid." << endl;
						}
						else {
							noError = false;
							Engine::GameState::current = Engine::GameState::states[1];
							cout << map.getName() << " is invalid, returning to load map state";
						}
					}

					//Record and print command effect.
					if (noError)
					{
						cmdEffect += "All maps were validated.\n";
						cout << "All maps were validated." << endl;
					}
					else
					{
						cmdEffect += "At least 1 map was invalid.\n";
						cout << "At least 1 map was invalid." << endl;
					}
				}
				else if (*cmd == "addplayer") {

					// TODO doesn't perfectly work yet
					if (Player::players.size() >= 6)
					{
						cout << "You have added the maximum amount of players. Please execute the gamestart command." << endl;
						noError = false;
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
					Engine::GameState::gamestartCmd(loadedMaps.front(), &Card::deck);

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

					cout << "TODO: Add verification before starting game." << endl;

					//Play the first map in the set, then remove it.
					mainGameLoop(loadedMaps.front());
					//Simulates .pop_front().
					loadedMaps.erase(loadedMaps.begin());
				}

				if (noError) {
					Engine::GameState::SwitchState(*Engine::GameState::current->links.at(nextStateIndex));
					cmdEffect += "Switched to other state using '" + cmd->value + "'.";
				}
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
