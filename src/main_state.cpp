#include "main_state.hpp"
#include "logger.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,
};

MainState::MainState(Engine& engine)
: GameState(engine), _shaderProgram(ShaderProgram::load("shaders/main")) {
	Logger::log("Constructing MainState");

	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

MainState::~MainState() {
	Logger::log("Destructing MainState");
}

void MainState::update(double) {
}

void MainState::draw() {
	glm::mat4 projMatrix = glm::perspective(45.0, 4.0 / 3.0, 0.1, 100.0);

	const float x = (std::cos(glfwGetTime() / 1.0)) * 1.0;
	const float y = (std::sin(glfwGetTime() / 1.0)) * 1.0;

	glm::mat4 viewMatrix = glm::lookAt(
		glm::vec3(x, y, 10),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, 1)
	);

	glm::mat4 modelMatrix(1.0);

	_shaderProgram.use();

	_shaderProgram.uniform("MVP", projMatrix * viewMatrix * modelMatrix);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaderProgram.bindBuffer("aPosition", GL_ARRAY_BUFFER, _vertexBuffer);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		0
	);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}
