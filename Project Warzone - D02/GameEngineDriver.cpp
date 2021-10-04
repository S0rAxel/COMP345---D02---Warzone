#include <stdio.h>
#include <iostream>
#include <iterator>
#include "GameEngine.h"

using namespace Engine;

void ControlFlow() {
	using namespace std;

	//Simply to avoid having to write out 'GameState::current' every time.
	GameState& current = *GameState::current;
	//Tracks if the 'end' command was given and if the control flow should end.
	bool endCmd = true;
	//The input command given by the user.
	std::string inputCmd;

	do {
		cout << "\nCurrent State: " << current.name << "\n";

		//Tracks if the given command is valid. Assume it won't be.
		bool validCmd = false;
		do {
			//Read next command.
			cin >> inputCmd;

			
			//'Outscoping' the loop index like this is not very good practice, 
			//but it is only for the requirements of assignment 1.
			short i;

			//Checks if the given command matches one of the state.
			for (i = 0; i < current.commands.size(); i++)
			{
				if (inputCmd == current.commands.at(i)) {
					validCmd = true;
					break;
				}
			}

			if (validCmd) {
				cout << "\nEnd prematurely? ";
				cin >> inputCmd;
				if(inputCmd == "y") {
					endCmd = false;
				}

				//If the command 'end' was valid, then we were in the 'win' state.
				if (inputCmd == "end") {
					endCmd = false;
				}
				//Otherwise, switch to the state of matching index.
				else {
					cout << "\nRecognized. Switching states...";
					//With 'outscoping', we can still access the index of the loop above.
					current = *GameState::SwitchState(*current.links.at(i));
				}
			}
			else {
				cout << "\nUnrecognized command '" << inputCmd << "'\n";
			}

		//If the given command was valid, then end the command check loop for this game state.
		} while (!validCmd);
	//If the 'end' command was given, then end the control flow. 
	} while (endCmd);
}

int main() {
	GameState::GameSetup();
	ControlFlow();
	GameState::GameExit();
}