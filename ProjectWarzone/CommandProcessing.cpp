#include "CommandProcessing.h"
#include "GameEngine.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#pragma region Command

//Constructors.
Command::Command(string value) : value(value), effect("None") { }
Command::Command() : Command("default") {}
Command::Command(const Command& toCopy) : Command(toCopy.value) { };

//Saves the command's effect.
//Should be called right after doing an action in reaction to the command.
void Command::saveEffect(string effect) {
	this->effect = effect;

	Notify(*this);
}

//Operators.
void Command::operator=(const Command& get) {
	this->value = get.value;
	this->effect = get.effect;
}
bool operator==(const Command& cmd, const string& str) {
	return _strcmpi((cmd.value.c_str()), str.c_str()) == 0;
}
bool operator==(const string& str, const Command& cmd) {
	return cmd == str;
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
CommandProcessor* CommandProcessor::current = nullptr;

//Selects the command processing mode.
void CommandProcessor::startup() {
	string input;

	do {
		cout << "Select input mode. (-console, -file)\n> ";
		cin >> input;

		if (input == "-console") {
			//Assign Console Processor to static Command Processor.
			current = new CommandProcessor();
			cout << "Command processor attached to: console.\n";
			break;
		}
		else if (input == "-file") {
			do {
				cout << "\nProvide an input file\n> ";
				cin >> input;

				//Assign File Processor to static Command Processor.
				current = new FileCommandProcessorAdapter(input);

				//Check if the File Processor found the given file.
				if ((dynamic_cast<FileCommandProcessorAdapter*>(current))->isOpen()) {
					cout << "Command processor attached to: " << input << ".\n";
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

//Reads input from console and generates a command.
Command* CommandProcessor::readCommand() {
	string input;
	cout << "\n> ";
	cin >> input;

	//Create a new command with the given input and save it.
	Command* userCommand = new Command(input);
	this->saveCommand(userCommand);

	return userCommand;
}
Command* CommandProcessor::getCommand() {
	return this->readCommand();
}

//Saves the command to the log.
void CommandProcessor::saveCommand(Command* cmd) {
	//Store the command in the command log.
	this->cmdLog.push_back(cmd);

	Notify(*this);
}

//Returns the index of the state transition matching the 
int CommandProcessor::validate(Command& cmd) {
	using namespace Engine;

	//Checks if the given command matches ones valid in the current state.
	for (int i = 0; i < GameState::current->commands.size(); i++) {
		//If it matches, return the index of the state (will be used for transition).
		if (cmd == GameState::current->commands.at(i)) {
			return i;
		}
	}

	//If this is reached then the given command matches
	//none of the valid ones in the current state.
	return -1;
}

//Prints the entirety of the command processor log to the console.
void CommandProcessor::printLog() {
	cout << "\n\nCommand Processor Log:\n\n";
	for (Command* cmd : CommandProcessor::current->cmdLog) {
		cout << *cmd << "\nEffect: " << cmd->effect << "\n\n";
	}
	cout << "\n\n";
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
	return "CommandProcessor::SaveCommand(): Command " + this->cmdLog.back()->value + " saved \n";
}

#pragma endregion

#pragma endregion

#pragma region FileLineReader
//Constructors.
FileLineReader::FileLineReader(string fileName) : fileName(fileName), fileStrm(fileName, ios::in) {
	if (fileStrm.is_open()) { cout << "File Command Processor attached to: " << fileName << endl; }
	else { cout << "Failed to open file '" << fileName << "'\n"; }
}
//May result in error.
FileLineReader::FileLineReader(const FileLineReader& ref) : fileStrm(fileName, ios::in) { }
//Destructor.
FileLineReader::~FileLineReader() {
	this->fileStrm.close();
}

//Reads the next input from the file and generates a command.
Command* FileLineReader::readCommand() {
	if (this->fileStrm.is_open()) {

		if (this->fileStrm.good()) {
			string fInput;
			this->fileStrm >> fInput;

			cout << "\n> " << fInput << endl;
			Command* fileCmd = new Command(fInput);

			return fileCmd;
		}
		//Abort process when file stream can't be read anymore.
		else if (this->fileStrm.eof()) {
			cout << "\nReached end of file.";
		}
		else {
			cout << "Error reading file.";
		}
		return new Command("$abort");
	}
	else {
		cout << "No input file to read.";
	}
	return new Command();
}
Command* FileLineReader::getCommand() {
	return this->readCommand();
}

//Checks if the file reader's stream is open.
bool FileLineReader::isOpen() {
	return (this->fileStrm && this->fileStrm.is_open());
}

//Operators
void FileLineReader::operator=(FileLineReader& get) {
	this->fileName = get.fileName;
	this->fileStrm.open(get.fileName);
}
ostream& operator<<(ostream& out, FileLineReader& fLineRead) {
	return out << "File Command Processor (" << fLineRead.fileName << ").";
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
Command* FileCommandProcessorAdapter::readCommand(string query) {
	throw std::logic_error("Method not implemented.");
}
//Reroutes the method call to the file reader and saves the output to log before returning it.
Command* FileCommandProcessorAdapter::getCommand() {
	//Re-route the call to the file processor.
	Command* cmd = this->fReader->getCommand();
	//Add the result to the command log and return.
	this->saveCommand(cmd);
	return cmd;
}

//Used to check if the command processor is able to read from file.
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