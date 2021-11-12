#include "CommandProcessing.h"
#include "GameEngine.h"

void CommandProcessingDemo() {

	Engine::GameState::GameSetup();

	system("pause");

	CommandProcessor::startup();
	Command cmd;
	int nextStateIndex;
	do {
		cmd = CommandProcessor::current->getCommand();

		//Special command, exits. For demo only.
		if (cmd == "$abort") {
			break;
		}
		//Special command, prints log of processor. For demo only.
		else if (cmd == "$log") {
			CommandProcessor::current->printLog();
		}
		else {
			//Check the validity of the command.
			nextStateIndex = CommandProcessor::validate(cmd);

			//If the state index isn't -1, switches to the state received by 'validate()'.
			if (nextStateIndex >= 0) {
				//If 'quit' was valid, then terminate the control flow.
				if (cmd == "quit") {
					break;
				}
				else {
					Engine::GameState::SwitchState(*Engine::GameState::current->links.at(nextStateIndex));
				}
			}
			else { cout << "Invalid Command\n\n"; }
		}
	} while (true);


	delete CommandProcessor::current;

	Engine::GameState::GameExit();

}