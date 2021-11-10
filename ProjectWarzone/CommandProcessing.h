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

	string value;
	string effect;
	void execute();
	void saveEffect();

		//void operator=(Command&);

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



class CommandProcessor : public Subject, ILoggable {
protected:
	vector<Command> cmdLog;

		//static void saveCommand(Command&);
	virtual Command readCommand(string);

public:
	CommandProcessor();
	//Polymorphism is allowed.
	virtual ~CommandProcessor();
	void saveCommand(Command&);

		//static vector<Command> cmdLog;
	static bool validate(Command&);

	virtual Command getCommand();

		//void operator=(CommandProcessor&);
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
	vector<Command> cmdLog;
	Command readCommand();

public:
	FileLineReader(string);
	FileLineReader(FileLineReader&);
	~FileLineReader();

	Command getCommand();

		//void operator=(FileCommandProcessor&);
	friend ostream& operator<<(ostream&, FileLineReader&);
};
ostream& operator<<(ostream&, FileLineReader&);



class FileCommandProcessorAdapter : public CommandProcessor {
private:
	FileLineReader* fProcess;
	Command readCommand(string);

public:
	FileCommandProcessorAdapter(string);
	FileCommandProcessorAdapter(FileLineReader*);
	~FileCommandProcessorAdapter();

	Command getCommand();

		//void operator=(FileCommandProcessorAdapter&);
	friend ostream& operator<<(ostream&, FileCommandProcessorAdapter&);
};
ostream& operator<<(ostream&, FileCommandProcessorAdapter&);