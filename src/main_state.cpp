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
_level("levels/level1") {
	Logger::log("Constructing MainState");
}

MainState::~MainState() {
	Logger::log("Destructing MainState");
}

void MainState::update(double dt, const Keyboard & keyboard) {
	float sideways = 0.0;
	float forward = 0.0;
	const float sideSpeed = 3.0;

	if (keyboard.isPressed(GLFW_KEY_UP)) {
		forward += 4.0;
	}

	if (keyboard.isPressed(GLFW_KEY_DOWN)) {
		forward -= 1.0;
	}

	if (keyboard.isPressed(GLFW_KEY_LEFT)) {
		sideways -= sideSpeed;
	}

	if (keyboard.isPressed(GLFW_KEY_RIGHT)) {
		sideways += sideSpeed;
	}

	_player.moveY(forward * dt);
	_player.moveX(sideways * dt);
}

void MainState::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projMatrix = glm::perspective(45.0, 4.0 / 3.0, 0.1, 100.0);

	const glm::vec3 playerPosition = _player.position();

	const glm::vec3 cameraPosition(playerPosition.x * 1.2, playerPosition.y - 5, 3);
	const glm::vec3 lightPosition(playerPosition.x, playerPosition.y - 2, 8);

	glm::mat4 viewMatrix = glm::lookAt(
		cameraPosition,
		playerPosition,
		glm::vec3(0, 0, 1)
	);

	glm::mat4 modelMatrix(1.0);

	glm::mat4 mvp = projMatrix * viewMatrix * modelMatrix;
	glm::mat4 normalMatrix = glm::inverseTranspose(viewMatrix * modelMatrix);

	_levelShader.use();
	_levelShader.uniform("uMVPMatrix", mvp);
	_levelShader.uniform("uNormalMatrix", normalMatrix);
	_levelShader.uniform("uLightPosition", lightPosition);
	_levelShader.uniform("uCameraPosition", cameraPosition);
	_level.render(_levelShader);

	modelMatrix = glm::translate(modelMatrix, playerPosition);

	mvp = projMatrix * viewMatrix * modelMatrix;
	normalMatrix = glm::inverseTranspose(viewMatrix * modelMatrix);

	_levelShader.uniform("uMVPMatrix", mvp);
	_levelShader.uniform("uNormalMatrix", normalMatrix);

	_player.render(_levelShader);
}
