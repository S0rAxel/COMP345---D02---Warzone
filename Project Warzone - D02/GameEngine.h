#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
namespace Engine {

	//Abstract class representing a state the game can be in.
	class GameState {
	public:
		//STATIC

		//Keeps track of the current game state.
		static GameState* current;
		//Holds the array of all game states (define in 'GameSetup').
		static GameState** states;

		//Creates an instance of each game state and establishes the connections between each.
		static void GameSetup();
		//Deallocates memory taken in 'GameSetup'.
		static void GameExit();
		//Safely switches from the current state to another.
		static GameState* SwitchState(GameState&);


		//INSTANCE

		//Allows custom behaviour on transition.
		virtual void Setup() = 0;
		virtual void Exit() = 0;

		//Name of the state.
		string name;

		//
		vector<GameState*> links;
		vector<string> commands;
	};
	

	namespace States {

		class Start : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			Start() {
				GameState::commands = { "loadmap" };
				name = "Start";
			}
			~Start() { }
		};

		class LoadMap : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			LoadMap() {
				GameState::commands = { "loadmap", "validatemap" };
				name = "Loaded Map";
			}
			~LoadMap() { }
		};

		class ValidMap : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			ValidMap() {
				GameState::commands = { "addplayer" };
				name = "Validated Map";
			}
			~ValidMap() { }
		};

		class AddPlayers : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			AddPlayers() {
				GameState::commands = { "addplayers", "assigncountries" };
				name = "Add Players";
			}
			~AddPlayers() { }
		};

		class AssignReinf : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			AssignReinf() {
				GameState::commands = { "issueorder" };
				name = "Assign Reinforcements";
			}
			~AssignReinf() { }
		};

		class IssueOrders : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			IssueOrders() {
				GameState::commands = { "issueorder", "endissueorders" };
				name = "Issue Orders";
			}
			~IssueOrders() { }
		};

		class ExecOrders : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			ExecOrders() {
				GameState::commands = { "execorder", "endexecorders", "win" };
				name = "Execute Orders";
			}
			~ExecOrders() { }
		};

		class GameOver : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			GameOver() {
				GameState::commands = { "play", "end" };
				name = "Win";
			}
			~GameOver() { }
		};
	}
}