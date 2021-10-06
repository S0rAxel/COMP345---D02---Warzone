#include "GameEngine.h"

using namespace Engine;
using namespace std;

//Start the program with the current state pointer at null.
GameState* GameState::current = nullptr;
GameState** GameState::states = nullptr;

void GameState::SwitchState(GameState& newState) {
	GameState::current->Exit();
	GameState::current = &newState;
	GameState::current->Setup();
}

using namespace States;

void GameState::GameSetup() {
	cout << "Game Setup...\n\tInitializing states...\n";

	//Initialize all game states.
	GameState::states = new GameState*[8]{
		new Start,
		new LoadMap,
		new ValidMap,
		new AddPlayers,
		new AssignReinf,
		new IssueOrders,
		new ExecOrders,
		new GameOver
	};

	cout << "\tEstablishing state links...\n";
	//Establish links between states.
	states[0]->links = { states[1] };
	states[1]->links = { states[1], states[2] };
	states[2]->links = { states[3] };
	states[3]->links = { states[3], states[4] };
	states[4]->links = { states[5] };
	states[5]->links = { states[5], states[6] };
	states[6]->links = { states[6], states[4], states[7] };
	states[7]->links = { states[0] };

	cout << "\tMoving to start state...\n";
	//Set the starting game state and call its setup function.
	GameState::current = states[0];
	GameState::current->Setup();
	cout << "Ready.\n\n";
}

void GameState::GameExit() {
	cout << "\n\nGame Exit...\n\tDeleting states...\n";
	//Loop through each element element of the array of pointers, de-allocating each.
	for (short i = 0; i < 8; i++) {
		delete *(GameState::states + i);
	}
	cout << "\tDe-allocating pointer array...\n";

	//De-allocate the array itself.
	delete GameState::states;
	cout << "Done.\n";
}


#pragma region State Constructors

//Base class default and initialization constructor.
//Default parameters are declared in header file.
GameState::GameState(string stateName, vector<string> cmds) : name(stateName), commands(cmds) {
	cout << "\t\tCreated state: " + this->name + "\n";
}
//Base class copy constructor.
GameState::GameState(GameState& toCopy) : name(toCopy.name), links(toCopy.links), commands(toCopy.commands) {
	cout << "\t\tCopied state " + toCopy.name << "\n";
}

//Base class destructor.
GameState::~GameState() {
	//Remove each pointer.
	for (short i = 0; i < links.size(); i++) {
		links.at(i) = nullptr;
	}
	cout << "\t\tDeleted state: " << this->name << "\n";
}


//Derived class default constructors.
//Funky table indentation. Hopefully easier to read.
Start::Start():				GameState(	"Start",					{ "loadmap" }							) { }
LoadMap::LoadMap():			GameState(	"Loaded Map",				{ "loadmap", "validatemap" }			) { }
ValidMap::ValidMap():			GameState(	"Validated Map",			{ "addplayer" }							) { }
AddPlayers::AddPlayers():		GameState(	"Add Players",				{ "addplayer", "assigncountries" }		) { }
AssignReinf::AssignReinf():	GameState(	"Assign Reinforcements",	{ "issueorder" }						) { }
IssueOrders::IssueOrders():	GameState(	"Issue Orders",				{ "issueorder", "endissueorders" }		) { }
ExecOrders::ExecOrders():		GameState(	"Execute Orders",			{ "execorder", "endexecorders", "win" }	) { }
GameOver::GameOver():			GameState(	"Win",						{ "play", "end" }						) { }

//Again, there are no destructors for the derived
//classes since they define no members (see header file).

#pragma endregion


#pragma region State Behavior

//Base class stream insertion operator.
ostream& Engine::operator<<(ostream& out, GameState& state) {
	out << state.name << " state.\nCommands: " << state.cmdList();
	return out;
}
//Base class assignment operator.
void GameState::operator=(GameState& other) {
	this->name = other.name;
	this->links = other.links;
	this->commands = other.commands;
}


//Gets the list of available commands to switch states.
string GameState::cmdList() {
	string toReturn = "(";

	for (string cmd : this->commands) {
		toReturn += cmd + ", ";
	}
	//Remove the last two characters (comma + space).
	toReturn.pop_back();
	toReturn.pop_back();
	toReturn += ")";

	return toReturn;
}


//These will allow for custom behavior for every state on transition.
//Nothing for now.

void Start::Setup() { }
void Start::Exit() { }

void LoadMap::Setup() { }
void LoadMap::Exit() { }

void ValidMap::Setup() { }
void ValidMap::Exit() { }

void AddPlayers::Setup() { }
void AddPlayers::Exit() { }

void AssignReinf::Setup() { }
void AssignReinf::Exit() { }

void IssueOrders::Setup() { }
void IssueOrders::Exit() { }

void ExecOrders::Setup() { }
void ExecOrders::Exit() { }

void GameOver::Setup() { }
void GameOver::Exit() { }

#pragma endregion