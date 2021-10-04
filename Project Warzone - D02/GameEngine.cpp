#include "GameEngine.h"

using namespace Engine;
using namespace std;

//Start the program with the current state pointer at null.
GameState* GameState::current = nullptr;
GameState** GameState::states = nullptr;

GameState* GameState::SwitchState(GameState& newState) {
	GameState::current->Exit();
	GameState::current = &newState;
	GameState::current->Setup();
	return &newState;
}

using namespace States;

void GameState::GameSetup() {
	cout << "Game Setup...\n";

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
	cout << "\tStates Initialized.\n";


	//Establish links between states.
	states[0]->links = { states[1] };
	states[1]->links = { states[1], states[2] };
	states[2]->links = { states[3] };
	states[3]->links = { states[3], states[4] };
	states[4]->links = { states[5] };
	states[5]->links = { states[5], states[6] };
	states[6]->links = { states[6], states[4], states[7] };
	states[7]->links = { states[0] };
	cout << "\tState Links Establised.\n";


	//Set the starting game state and call its setup function.
	GameState::current = states[0];
	GameState::current->Setup();
	cout << "Ready.\n\n";

	//Pointer to the states array will be lost here.
	//This isn't a problem, though. Since all states are linked to eachother then 
	//each state remains ultimately accessible (as long as 'current' isn't cleared).
}

void GameState::GameExit() {
	cout << "\n\n\nGame Exit...\n";
	//Loop through each element element of the array of pointers, de-allocating each.
	for (short i = 0; i < 8; i++) {
		delete *(GameState::states + i);
	}
	cout << "\tDe-allocated states.\n";

	//De-allocate the array itself.
	delete GameState::states;
	cout << "\tDe-allocated pointer array.\nDone.\n";
}


#pragma region State Details

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