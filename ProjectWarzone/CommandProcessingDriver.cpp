#include "CommandProcessing.h"

void CommandProcessingDemo() {
	system("pause");

	CommandProcessor::startup();
	Command cmd;
	do {
		cmd = CommandProcessor::cmdProcessor->getCommand();
	} while (CommandProcessor::cmdProcessor->validate(cmd));


	delete CommandProcessor::cmdProcessor;
}