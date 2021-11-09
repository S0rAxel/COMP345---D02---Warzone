#include "CommandProcessing.h"
#include "GameEngine.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;



#pragma region Command

Command::Command(string value) : value(value) { }
Command::Command() : Command("default") {}

void Command::execute() {
	cout << "Executing command: " << this->value;
}

void Command::saveEffect() {
	this->effect = "Achieved: " + this->value;
}

ostream& operator<<(ostream& out, Command& cmd) {
	return out << "Command: " << cmd.value;
}

#pragma endregion

//
	//cout << "Command Processor attached to: Console.\n";


#pragma region CommandProcessor
CommandProcessor::CommandProcessor() { }
CommandProcessor::~CommandProcessor() { }

	//vector<Command> CommandProcessor::cmdLog{};

Command CommandProcessor::readCommand(string query) {
	string input;
	cin >> input;

	Command userCommand(input);
		//do {
		//	cout << query << "\n> ";
		//	cin >> userCommand.value;

		//	if (this->validate(userCommand)) { break; }
		//	else { cout << "Invalid command.\n\n"; }

		//} while (true);

	this->saveCommand(userCommand);

	return userCommand;
}

Command CommandProcessor::getCommand() {
	return this->readCommand("Question.");
}

void CommandProcessor::saveCommand(Command& cmd) {
	//Store the command in the command log.
	this->cmdLog.push_back(cmd);
}

bool CommandProcessor::validate(Command& cmd) {
	using namespace Engine;

	//Checks if the given command matches ones valid in the current state.
	for (string validCmd : GameState::current->commands) {
		if (cmd.value == validCmd) {
			return true;
		}
	}

	//If this is reached then the given command matches
	//none of the valid ones in the current state.
	return false;
}

ostream& operator<<(ostream& out, CommandProcessor& cmdProcess) {
		//return out << "Console Command Processor.\n";
	return out << "Console Command Processor. Log of "
		<< cmdProcess.cmdLog.size() << " commands.";
}

#pragma endregion



#pragma region FileLineReader
//Constructors.
FileLineReader::FileLineReader(string fileName) : targetFile(fileName), fileStrm(targetFile, ios::in) {
	if (fileStrm.is_open()) { cout << "File Command Processor attached to: " << targetFile << endl; }
	else { cout << "Failed to open file '" << targetFile <<"'\n"; }
}
FileLineReader::FileLineReader(FileLineReader& ref) : fileStrm(targetFile, ios::in) { }
//Destructor.
FileLineReader::~FileLineReader() {
	this->fileStrm.close();
}


Command FileLineReader::readCommand() {
	if (this->fileStrm.is_open()) {

		string fInput;
		this->fileStrm >> fInput;

		cout << "\n> " << fInput << endl;
		Command fileCmd(fInput);

		if (!CommandProcessor::validate(fileCmd)) { cout << "Invalid command.\n\n"; }
		return fileCmd;
	}
	else {
		cout << "Failed to read.";
	}
	return Command();
}

Command FileLineReader::getCommand() {
	return this->readCommand();
}

ostream& operator<<(ostream& out, FileLineReader& fLineRead) {
	return out << "File Command Processor (" << fLineRead.targetFile << ").";
}

#pragma endregion



#pragma region Adapter

//Constructors.
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* fLineRead) : fProcess(fLineRead) { }
FileCommandProcessorAdapter::FileCommandProcessorAdapter(string targetFile) : fProcess(new FileLineReader(targetFile)) { }
//Destructor.
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() { delete fProcess; }

//
Command FileCommandProcessorAdapter::readCommand(string query) {
	throw std::logic_error("Method not implemented.");
}

Command FileCommandProcessorAdapter::getCommand() {
	//Re-route the call to the file processor.
	Command cmd = this->fProcess->getCommand();
	//Add the result to the command log and return.
	CommandProcessor::saveCommand(cmd);
	return cmd;
}

ostream& operator<<(ostream& out, FileCommandProcessorAdapter& fCmdAdapt) {
		//return out << "File Command Processor Adapter. Contains:\n\t" << fCmdProcessAdapt.fProcess << endl;
	return out << "File Command Processor Adapter. Contains:\n\t" 
		<< fCmdAdapt.fProcess << "\nLog of " 
		<< fCmdAdapt.cmdLog.size() << " commands.";
}

#pragma endregion