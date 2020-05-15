#ifndef MAIN_STATE_HPP
#define MAIN_STATE_HPP

#include "game_state.hpp"
#include "engine.hpp"
#include "shader_program.hpp"
#include "player.hpp"
#include "level.hpp"
#include "framebuffer.hpp"
#include "screen_renderer.hpp"

class MainState : public GameState {
	public:
		MainState(Engine& engine);
		~MainState();

		void setup() { }
		void pause() { }
		void update(double, const Keyboard &);
		void draw();

	private:
		Framebuffer _framebuffer;
		ScreenRenderer _screenRenderer;
		ShaderProgram _levelShader;
		ShaderProgram _fireShader;

		Player _player;
		Level _level;
};

#endif
