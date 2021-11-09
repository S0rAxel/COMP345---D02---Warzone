#include "CommandProcessing.h"

void CommandProcessingDemo() {
	system("pause");

	CommandProcessor* processor;
	string input;

	do {
		cout << "Select input mode. (-console, -file)\n> ";
		cin >> input;

		if (input == "-console") {
			processor = new CommandProcessor();
			break;
		}
		else if (input == "-file") {
			cout << "\nProvide an input file\n> ";
			cin >> input;
			processor = new FileCommandProcessorAdapter(input);
			break;
		}
		else {
			cout << "Invalid command.\n\n";
		}
	} while (true);

	//cout << "\n\nUsing: " << *processor << endl;
	 
	Command cmd;
	do {
		cmd = processor->getCommand();
		cout << cmd;
	} while (processor->validate(cmd));

	delete processor;
}