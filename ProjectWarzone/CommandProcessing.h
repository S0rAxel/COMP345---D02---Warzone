#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "LoggingObserver.h"

using namespace std;


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



class CommandProcessor : public Subject, ILoggable {
protected:
	vector<Command> cmdLog;
	virtual Command readCommand();

public:
	//Static members
	void saveCommand(Command&);
	static CommandProcessor* current;
	static void startup();
	static int validate(Command&);


	CommandProcessor();
	CommandProcessor(const CommandProcessor&);
	//Polymorphism is allowed.
	virtual ~CommandProcessor();

	//Instance members
	virtual Command getCommand();
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



class FileLineReader {
private:
	string targetFile;
	ifstream fileStrm;

	Command readCommand();

public:
	FileLineReader(string);
	FileLineReader(const FileLineReader&);
	~FileLineReader();

	Command getCommand();
	bool isOpen();

	void operator=(FileLineReader&);
	friend ostream& operator<<(ostream&, FileLineReader&);
};
ostream& operator<<(ostream&, FileLineReader&);



class FileCommandProcessorAdapter : public CommandProcessor {
private:
	FileLineReader* fReader;
	Command readCommand(string);

public:
	FileCommandProcessorAdapter(string);
	FileCommandProcessorAdapter(FileLineReader*);
	FileCommandProcessorAdapter(const FileCommandProcessorAdapter&);
	~FileCommandProcessorAdapter();

	Command getCommand();
	bool isOpen();

	void operator=(FileCommandProcessorAdapter&);
	friend ostream& operator<<(ostream&, FileCommandProcessorAdapter&);
};
ostream& operator<<(ostream&, FileCommandProcessorAdapter&);