#pragma once
#include <stdio.h>
#include <iostream>

namespace Engine {

	//Abstract class representing a state the game can be in.
	class GameState {
	public:
		virtual void Setup();
		virtual void Exit();
	};

	//Holds the current GameState.
	GameState* current;
	//Free function to switch from one state to another.
	void SwitchState(GameState&);

	//Example of implementation of GameState abstract class.
	class StartState : GameState {
		void Setup();
		void Exit();

		//Constructor.
		StartState() { }

		//Destructor.
		~StartState() { }
	};
}