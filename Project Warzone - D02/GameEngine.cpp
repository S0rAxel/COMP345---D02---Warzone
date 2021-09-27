#include "GameEngine.h"

using namespace Engine;

void SwitchState(GameState& newState) {
	current->Exit();
	current = &newState;
	current->Setup();
}