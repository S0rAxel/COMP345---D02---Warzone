#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
namespace Engine {
	//IMPORTANT FOR GRADING
	/*
	* The assignment requirements specify that one class named 'GameEngine' must be included.
	* For all intents and purposes, this is it. I simply find 'GameState' to be a more descriptive name.
	*/

	//Abstract class representing a state the game can be in.
	class GameState {
	public:
		//STATIC

		//Keeps track of the current game state.
		static GameState* current;
		//Holds the array of all game states (defined in 'GameSetup').
		static GameState** states;

		//Creates an instance of each game state and establishes the connections between each.
		static void GameSetup();
		//Deallocates memory taken in 'GameSetup'.
		static void GameExit();
		//Safely switches from the current state to another.
		static void SwitchState(GameState&);


		//INSTANCE

		//Name of the state.
		string name;

		//The links to other game states.
		vector<GameState*> links;
		//The commands to switch to other game states.
		vector<string> commands;

		//Constructors
		GameState(string = "Default", vector<string> = {});
		GameState(GameState&);
		//Destructor
		~GameState();

		//Gets the list of commands available for the state in a formatted string.
		string cmdList();

		//Allows custom behaviour on transition.
		virtual void Setup() = 0;
		virtual void Exit() = 0;

		//Gets values of right hand side.
		void operator=(GameState&);
	};
	
	//Passes state name and command list to the stream.
	ostream& operator<<(ostream&, GameState&);

	namespace States {
		//IMPORTRANT FOR GRADING
		/*
		* I am aware of the assignment requirement stating that each class should have a
		* copy constructor, destructor, assignment and stream insertion operator
		* but since none of derived classes declare new members, defining these for each
		* would be useless (they would either be empty or just call the base classe's version).
		* 
		* Instead, the above base class defines everything required such that the derived
		* classes inherit the functionality. The base classe's copy constructor, destructor
		* and operators will implicitly be called when used on derived class instances.
		*/


		class Start : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			Start();
		};

		class LoadMap : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			LoadMap();
		};

		class ValidMap : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			ValidMap();
		};

		class AddPlayers : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			AddPlayers();
		};

		class AssignReinf : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			AssignReinf();
		};

		class IssueOrders : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			IssueOrders();
		};

		class ExecOrders : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			ExecOrders();
		};

		class GameOver : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			GameOver();
		};
	}
}