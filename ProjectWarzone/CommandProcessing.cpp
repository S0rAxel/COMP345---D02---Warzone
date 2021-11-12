#include "CommandProcessing.h"
#include "GameEngine.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

#pragma region Command

//Constructors.
Command::Command(string value) : value(value), effect("None") { }
Command::Command() : Command("default") {}
Command::Command(const Command& toCopy) : Command(toCopy.value) { };

void Command::execute() {
	cout << "Executing command: " << this->value;
}

//Temporary. Not sure how to get a more descirptive message.
void Command::saveEffect() {
	this->effect = "Achieved: " + this->value;

	Notify(*this);
}

//Operators.
void Command::operator=(const Command& get) {
	this->value = get.value;
	this->effect = get.effect;
}
ostream& operator<<(ostream& out, Command& cmd) {
	return out << "Command: " << cmd.value;
}

#pragma region Subject and ILoggable
void Command::Attach(Observer* obs)
{
	Subject::Attach(obs);
}

void Command::Detach(Observer* obs)
{
	Subject::Detach(obs);
}

void Command::Notify(ILoggable& log)
{
	Subject::Notify(log);
}

string Command::StringToLog()
{
	return "Command::saveEffect(): " + this->effect + "\n";
}

#pragma endregion

#pragma endregion



#pragma region CommandProcessor

//Constructors.
CommandProcessor::CommandProcessor() { }
CommandProcessor::CommandProcessor(const CommandProcessor& toCopy) : cmdLog(toCopy.cmdLog) { }
CommandProcessor::~CommandProcessor() { }

//Initial value.
CommandProcessor* CommandProcessor::cmdProcessor = nullptr;

//Selects the command processing mode.
void CommandProcessor::startup() {
	string input;

	do {
		cout << "Select input mode. (-console, -file)\n> ";
		cin >> input;

		if (input == "-console") {
			//Assign Console Processor to static Command Processor.
			cmdProcessor = new CommandProcessor();
			break;
		}
		else if (input == "-file") {
			do {
				cout << "\nProvide an input file\n> ";
				cin >> input;

				//Assign File Processor to static Command Processor.
				cmdProcessor = new FileCommandProcessorAdapter(input);

				//Check if the File Processor found the given file.
				if ((dynamic_cast<FileCommandProcessorAdapter*>(cmdProcessor))->isOpen()) {
					break;
				}

			//Loop until a valid file is given.
			} while (true);
			break;
		}
		else {
			cout << "Invalid command processing mode.\n\n";
		}
	//Loop until a valid command is given.
	} while (true);
}


Command CommandProcessor::readCommand() {
	string input;
	cout << "\n> ";
	cin >> input;

	//Create a new command with the given input and save it.
	Command userCommand(input);
	this->saveCommand(userCommand);

	return userCommand;
}

Command CommandProcessor::getCommand() {
	return this->readCommand();
}

void CommandProcessor::saveCommand(Command& cmd) {
	//Store the command in the command log.
	this->cmdLog.push_back(cmd);

	Notify(*this);
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


//Operators
void CommandProcessor::operator=(CommandProcessor& get) {
	this->cmdLog = get.cmdLog;
}
ostream& operator<<(ostream& out, CommandProcessor& cmdProcess) {
	return out << "Console Command Processor. Log of "
		<< cmdProcess.cmdLog.size() << " commands.";
}

#pragma region Subject and ILoggable
void CommandProcessor::Attach(Observer* obs)
{
	Subject::Attach(obs);
}

void CommandProcessor::Detach(Observer* obs)
{
	Subject::Detach(obs);
}

void CommandProcessor::Notify(ILoggable& log)
{
	Subject::Notify(log);
}

string CommandProcessor::StringToLog()
{
	return "CommandProcessor::SaveCommand(): Command " + this->cmdLog.back().value + " saved \n";
}

#pragma endregion

#pragma endregion



#pragma region FileLineReader
//Constructors.
FileLineReader::FileLineReader(string fileName) : targetFile(fileName), fileStrm(targetFile, ios::in) {
	if (fileStrm.is_open()) { cout << "File Command Processor attached to: " << targetFile << endl; }
	else { cout << "Failed to open file '" << targetFile <<"'\n"; }
}
//May result in error.
FileLineReader::FileLineReader(const FileLineReader& ref) : fileStrm(targetFile, ios::in) { }
//Destructor.
FileLineReader::~FileLineReader() {
	this->fileStrm.close();
}


Command FileLineReader::readCommand() {
	if (this->fileStrm.is_open() && this->fileStrm.good()) {

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

bool FileLineReader::isOpen() {
	return (this->fileStrm && this->fileStrm.is_open());
}

//Operators
void FileLineReader::operator=(FileLineReader& get) {
	this->targetFile = get.targetFile;
	this->fileStrm.open(get.targetFile);
}
ostream& operator<<(ostream& out, FileLineReader& fLineRead) {
	return out << "File Command Processor (" << fLineRead.targetFile << ").";
}

#pragma endregion



#pragma region Adapter

//Constructors.
FileCommandProcessorAdapter::FileCommandProcessorAdapter(string targetFile) : fReader(new FileLineReader(targetFile)) { }
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* fileReader) : fReader(fileReader) { }
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& toCopy) : FileCommandProcessorAdapter(fReader) { }
//Destructor.
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() { delete fReader; }

//This command can't be called outside the class and shouldn't be anyway.
Command FileCommandProcessorAdapter::readCommand(string query) {
	throw std::logic_error("Method not implemented.");
}

Command FileCommandProcessorAdapter::getCommand() {
	//Re-route the call to the file processor.
	Command cmd = this->fReader->getCommand();
	//Add the result to the command log and return.
	this->saveCommand(cmd);
	return cmd;
}

bool FileCommandProcessorAdapter::isOpen() {
	return this->fReader->isOpen();
}

//Operators.
void FileCommandProcessorAdapter::operator=(FileCommandProcessorAdapter& get) {
	this->cmdLog = get.cmdLog;
	*this->fReader = *get.fReader;
}
ostream& operator<<(ostream& out, FileCommandProcessorAdapter& fCmdAdapt) {
	return out << "File Command Processor Adapter. Contains:\n\t" 
		<< fCmdAdapt.fReader << "\nLog of " 
		<< fCmdAdapt.cmdLog.size() << " commands.";
}

#pragma endregion