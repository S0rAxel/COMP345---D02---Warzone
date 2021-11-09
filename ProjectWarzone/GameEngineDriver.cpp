/*#include <stdio.h>
#include <iostream>
#include <iterator>
#include "GameEngine.h"
#include "GameEngineDriver.h"

using namespace Engine;

//Main game loop. Gets commands from the user and perform 
//state transitionsuntil the 'end' command is given.
void ControlFlow() {
	using namespace std;

	//Simply to avoid having to write out 'GameState::current' every time.
	GameState* current = GameState::current;
	//Tracks if the 'end' command was given and if the control flow should end.
	bool endCmd = true;
	//The input command given by the user.
	std::string inputCmd;

	cout << "\n---------------------------\n\t| WARZONE |\n---------------------------\n";

	do {
		cout << "\nCurrent State: " << current->name << "\nCommands: " + current->cmdList() + "\n";

		//Tracks if the given command is valid. Assume it won't be.
		bool validCmd = false;
		do {
			//Read next command.
			cin >> inputCmd;

			
			//'Outscoping' the loop index like this is not very good practice, 
			//but it is only for the requirements of assignment 1.
			short i;

			//Checks if the given command matches one of the state.
			for (i = 0; i < current->commands.size(); i++)
			{
				if (inputCmd == current->commands.at(i)) {
					validCmd = true;
					break;
				}
			}

			if (validCmd) {
				//If the command 'end' was valid, then we were in the 'win' state.
				if (inputCmd == "end") {
					endCmd = false;
				}
				//Otherwise, switch to the state of matching index.
				else {
					cout << "Recognized. Switching states...\n";
					//With 'outscoping', we can still access the index of the loop above.
					GameState::SwitchState(*(current->links.at(i)));
					current = GameState::current;
				}
			}
			else {
				cout << "\nUnrecognized command '" << inputCmd << "'\nCommands: " + current->cmdList() + "\n";
			}

		//If the given command was valid, then end the command check loop for this game state.
		} while (!validCmd);
	//If the 'end' command was given, then end the control flow. 
	} while (endCmd);
}

void GameEngineDriverDemo() {
	GameState::GameSetup();
	ControlFlow();
	GameState::GameExit();
}*/