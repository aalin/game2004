#ifndef MAIN_STATE_HPP
#define MAIN_STATE_HPP

#include "game_state.hpp"
#include "engine.hpp"
#include "shader_program.hpp"
#include "mesh.hpp"

class MainState : public GameState {
	public:
		MainState(Engine& engine);
		~MainState();

		void setup() { }
		void pause() { }
		void update(double, const Keyboard &);
		void draw();

	private:
		ShaderProgram _shaderProgram;
		Mesh _triangleMesh;
};

#endif
