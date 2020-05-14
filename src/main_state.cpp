#include "main_state.hpp"
#include "logger.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cmath>

MainState::MainState(Engine& engine) :
GameState(engine),
_shaderProgram(ShaderProgram::load("shaders/main")),
_levelShader(ShaderProgram::load("shaders/level")),
_triangleMesh(Mesh::PrimitiveType::Triangles),
_level("levels/level1") {
	Logger::log("Constructing MainState");

	_triangleMesh.addBuffer("aPosition", std::vector<glm::vec3>({
		glm::vec3(-1.0f,-1.0f, 5.0f),
		glm::vec3( 1.0f,-1.0f, 5.0f),
		glm::vec3(-1.0f, 1.0f, 5.0f),
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

void MainState::update(double, const Keyboard &) {
}

void MainState::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projMatrix = glm::perspective(45.0, 4.0 / 3.0, 0.1, 100.0);

	const float x = (std::cos(glfwGetTime() / 1.0)) * 2.0;
	const float y = std::fmod(glfwGetTime(), 50.0) - 5;

	const glm::vec3 cameraPosition(x, y, 5);

	glm::mat4 viewMatrix = glm::lookAt(
		cameraPosition,
		glm::vec3(0, y + 10, 0),
		glm::vec3(0, 0, 1)
	);

	glm::mat4 modelMatrix(1.0);

	glm::mat4 mvp = projMatrix * viewMatrix * modelMatrix;
	glm::mat4 normalMatrix = glm::inverseTranspose(viewMatrix * modelMatrix);

	_levelShader.use();
	_levelShader.uniform("uMVPMatrix", mvp);
	_levelShader.uniform("uNormalMatrix", normalMatrix);
	_levelShader.uniform("uLightPosition", glm::vec3(x, y + 5, 10));
	_levelShader.uniform("uCameraPosition", cameraPosition);
	_level.render(_levelShader);

	//_shaderProgram.use();
	//_shaderProgram.uniform("MVP", mvp);
	//_triangleMesh.render(_shaderProgram);

}
