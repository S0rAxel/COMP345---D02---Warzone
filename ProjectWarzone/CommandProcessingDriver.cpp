#include "CommandProcessing.h"
#include "GameEngine.h"
#include "Map.h"
#include "Drivers.h"

Map readfile(string);

//Demonstrates the functionality of the command processing part.
void CommandProcessingDemo(Observer& obs) {
	Engine::GameState::GameSetup();

	system("pause");

	CommandProcessor::startup();
	Command* cmd;
	Command* followUp;
	string cmdEffect;

	int nextStateIndex;
	do {
		cmd = CommandProcessor::current->getCommand();
		cmd->Attach(&obs);
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

				//I should not be doing this. This functionality is supposed to be in part 2.
				else if (*cmd == "loadmap") {
					cout << "\nEnter the map's file name:";

					followUp = CommandProcessor::current->getCommand();
					followUp->Attach(&obs);
					followUp->saveEffect("Follow-up of last command.");

					//Record and print command effect.
					cmdEffect += "Loaded map file: " + followUp->value + ".\n";
					cout << "Loaded map file: " << followUp->value << endl;
				}
				else if (*cmd == "addplayer") {
					cout << "\nEnter the player's name";

					followUp = CommandProcessor::current->getCommand();
					followUp->saveEffect("Follow-up of last command.");

					cmdEffect += "Added player " + followUp->value + ".\n";
					cout << "Added player " + followUp->value << endl;
				}

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