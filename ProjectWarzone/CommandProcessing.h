#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "LoggingObserver.h"

using namespace std;

//Represents a command given by the user. Either taken from the console or from a file.
class Command : public Subject, ILoggable {
public:
	Command();
	Command(string);
	Command(const Command&);

	string value;
	string effect;
	void saveEffect(string);

	void operator=(const Command&);
	friend ostream& operator<<(ostream&, Command&);
	//Allows command processors to freely manipulate Command objects.
	friend class CommandProcessor;
	friend class FileLineReader;


#pragma region Subject and ILoggable implementation
	void Attach(Observer* obs);
	void Detach(Observer* obs);
	void Notify(ILoggable& log);
	string StringToLog();
#pragma endregion

};
ostream& operator<<(ostream&, Command&);
bool operator==(const Command&, const string&);
bool operator==(const string&, const Command&);



//Processes user input taken from the console. Uses 'Commands' as main commnication object.
class CommandProcessor : public Subject, ILoggable {
protected:
	vector<Command*> cmdLog;
	virtual Command* readCommand();

public:
	//Static members
	void saveCommand(Command*);
	static CommandProcessor* current;
	static void startup();
	static int validate(Command&);


	CommandProcessor();
	CommandProcessor(const CommandProcessor&);
	//Virtual since polymorphism is allowed.
	virtual ~CommandProcessor();

	//Instance members
	virtual Command* getCommand();
	void printLog();

	//Opeators.
	void operator=(CommandProcessor&);
	friend ostream& operator<<(ostream&, CommandProcessor&);
	

	// Implementing methods from parent abstract classes
#pragma region Subject and ILoggable implementation
	void Attach(Observer* obs);
	void Detach(Observer* obs);
	void Notify(ILoggable& log);
	string StringToLog();
#pragma endregion

};
ostream& operator<<(ostream&, CommandProcessor&);



//Processes user input taken from files. Uses 'Commands' as main commnication object.
class FileLineReader {
private:
	string fileName;
	ifstream fileStrm;

	Command* readCommand();

public:
	FileLineReader(string);
	FileLineReader(const FileLineReader&);
	~FileLineReader();

	Command* getCommand();
	bool isOpen();

	void operator=(FileLineReader&);
	friend ostream& operator<<(ostream&, FileLineReader&);
};
ostream& operator<<(ostream&, FileLineReader&);



//Adapts the 'FileLineReader' class to be used polymorphically as a 'CommandProcessor' followin the Adapter design pattern.
class FileCommandProcessorAdapter : public CommandProcessor {
private:
	FileLineReader* fReader;
	Command* readCommand(string);

public:
	FileCommandProcessorAdapter(string);
	FileCommandProcessorAdapter(FileLineReader*);
	FileCommandProcessorAdapter(const FileCommandProcessorAdapter&);
	~FileCommandProcessorAdapter();

	Command* getCommand();
	bool isOpen();

	void operator=(FileCommandProcessorAdapter&);
	friend ostream& operator<<(ostream&, FileCommandProcessorAdapter&);
};
ostream& operator<<(ostream&, FileCommandProcessorAdapter&);