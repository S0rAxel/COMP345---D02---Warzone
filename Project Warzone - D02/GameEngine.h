#pragma once
#include <stdio.h>
#include <iostream>

namespace Engine {

	//Abstract class representing a state the game can be in.
	class GameState {
	public:
		virtual void Setup() = 0;
		virtual void Exit() = 0;

		GameState *links;
		std::string* commands;
	};


	//Holds the current GameState.
	GameState* current;
	
	//Free function to switch from one state to another.
	void SwitchState(GameState&);

	//Creates an instance of each game state and establishes the connections between each.
	void GameSetup();


	namespace States {

		//Example of implementation of GameState abstract class.
		class Example : public GameState {
			void GameState::Setup();
			void GameState::Exit();

			//Constructor.
			Example() {
				GameState::commands = new std::string[1]{ "command" };
			}

			//Destructor.
			~Example() { }
		};


		class Start : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			Start() {
				GameState::commands = new std::string[1]{ "loadmap" };
			}
			~Start() { }
		};

		class LoadMap : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			LoadMap() {
				GameState::commands = new std::string[2]{ "loadmap", "validatemap" };
			}
			~LoadMap() { }
		};

		class ValidMap : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			ValidMap() {
				GameState::commands = new std::string[1]{ "addplayers" };
			}
			~ValidMap() { }
		};

		class AddPlayers : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			AddPlayers() {
				GameState::commands = new std::string[2]{ "addplayers", "assigncountries" };
			}
			~AddPlayers() { }
		};

		class AssignReinf : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			AssignReinf() {
				GameState::commands = new std::string[1]{ "issueorder" };
			}
			~AssignReinf() { }
		};

		class IssueOrders : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			IssueOrders() {
				GameState::commands = new std::string[2]{ "issueorder", "endissueorders" };
			}
			~IssueOrders() { }
		};

		class ExecOrders : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			ExecOrders() {
				GameState::commands = new std::string[3]{ "execorder", "endexecorders", "win" };
			}
			~ExecOrders() { }
		};

		class GameOver : public GameState {
		public:
			void GameState::Setup();
			void GameState::Exit();

			GameOver() {
				GameState::commands = new std::string[2]{ "play", "end" };
			}
			~GameOver() { }
		};
	}
}