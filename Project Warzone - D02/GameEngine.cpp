#include "GameEngine.h"

using namespace Engine;

void SwitchState(GameState& newState) {
	current->Exit();
	current = &newState;
	current->Setup();
}

void GameSetup() {
	using namespace States;

	//Initialize all game states.
	GameState* states[8] = {
		new Start,
		new LoadMap,
		new ValidMap,
		new AddPlayers,
		new AssignReinf,
		new IssueOrders,
		new ExecOrders,
		new GameOver
	};
	
	//Establish links between states.
	//Doesn't work right now because 'arrays of abstract functions are not allowed'.
	states[0]->links = new GameState[1]{ *states[1] };
	states[1]->links = new GameState[2]{ *states[1], *states[2] };
	states[2]->links = new GameState[1]{ *states[3] };
	states[3]->links = new GameState[2]{ *states[3], *states[4] };
	states[4]->links = new GameState[1]{ *states[5] };
	states[5]->links = new GameState[2]{ *states[5], *states[6] };
	states[6]->links = new GameState[3]{ *states[6], *states[4], *states[7] };
	states[7]->links = new GameState[1]{ *states[0] };

	//Set the starting game state and call its setup function.
	current = states[0];
	current->Setup();
}