#ifndef MAIN_STATE_HPP
#define MAIN_STATE_HPP

#include "game_state.hpp"
#include "engine.hpp"

class MainState : public GameState {
	public:
		MainState(Engine& engine) : GameState(engine) { }
		~MainState() {}

		void setup() { }
		void pause() { }
		void update(double) { }
		void draw() { }
		void keyPress(int) { }
		void keyRelease(int) { }
};

#endif
