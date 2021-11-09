#pragma once
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


class Command {
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
};
ostream& operator<<(ostream&, Command&);



class CommandProcessor {
protected:
	vector<Command> cmdLog;

		//static void saveCommand(Command&);
	void saveCommand(Command&);
	virtual Command readCommand(string);

public:
	CommandProcessor();
	//Polymorphism is allowed.
	virtual ~CommandProcessor();

		//static vector<Command> cmdLog;
	static bool validate(Command&);

	virtual Command getCommand();

		//void operator=(CommandProcessor&);
	friend ostream& operator<<(ostream&, CommandProcessor&);
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