#ifndef MAIN_STATE_HPP
#define MAIN_STATE_HPP

#include "game_state.hpp"
#include "engine.hpp"
#include "shader_program.hpp"

class MainState : public GameState {
	public:
		MainState(Engine& engine);
		~MainState();

		void setup() { }
		void pause() { }
		void update(double);
		void draw();
		void keyPress(int) { }
		void keyRelease(int) { }
	private:
		ShaderProgram _shaderProgram;
		GLuint _vertexBuffer;
		GLuint _colorBuffer;
};

#endif
