#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "engine.hpp"

class GameState {
	public:
		GameState(Engine &game) : _game(game) { }
		virtual ~GameState() { }

		virtual void setup() = 0;
		virtual void pause() = 0;
		virtual void update(double s) = 0;
		virtual void draw() = 0;

		virtual void keyPress(int key ) = 0;
		virtual void keyRelease(int key) = 0;

	protected:
		Engine& getGame() { return _game; };

	private:
		Engine &_game;
};

#endif
