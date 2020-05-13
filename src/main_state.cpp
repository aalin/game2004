#include "main_state.hpp"
#include "logger.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

MainState::MainState(Engine& engine)
	:	GameState(engine),
		_shaderProgram(ShaderProgram::load("shaders/main")),
		//_triangleMesh(Mesh::PrimitiveType::Triangles) {
		_triangleMesh(GL_TRIANGLES) {
	Logger::log("Constructing MainState");

	_triangleMesh.addBuffer("aPosition", std::vector<glm::vec3>({
		glm::vec3(-1.0f,-1.0f, 0.0f),
		glm::vec3( 1.0f,-1.0f, 0.0f),
		glm::vec3(-1.0f, 1.0f, 0.0f),
	}));

	_triangleMesh.addBuffer("aColor", std::vector<glm::vec3>({
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
	}));
}

MainState::~MainState() {
	Logger::log("Destructing MainState");
}

void MainState::update(double) {
}

void MainState::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	_triangleMesh.render(_shaderProgram);
}
