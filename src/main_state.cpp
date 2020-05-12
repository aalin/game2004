#include "main_state.hpp"
#include "logger.hpp"

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
};

MainState::MainState(Engine& engine)
: GameState(engine), _shaderProgram(ShaderProgram::load("shaders/main")) {
	Logger::log("Constructing MainState");
}

MainState::~MainState() {
	Logger::log("Destructing MainState");
}

void MainState::update(double) {
}

void MainState::draw() {
	Logger::log("Shader program id", _shaderProgram.getId());
}
