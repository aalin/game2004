#include "main_state.hpp"
#include "logger.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cmath>

MainState::MainState(Engine& engine) :
GameState(engine),
_framebuffer(engine.width(), engine.height(), 0),
_levelShader(ShaderProgram::load("shaders/level")),
_fireShader(ShaderProgram::load("shaders/fire")),
_level("levels/level1") {
	Logger::log("Constructing MainState");
}

MainState::~MainState() {
	Logger::log("Destructing MainState");
}

void MainState::update(double dt, const Keyboard & keyboard) {
	float sideways = 0.0;
	float forward = 0.0;

	if (keyboard.isPressed(GLFW_KEY_UP)) {
		forward += 1.0;
	}

	if (keyboard.isPressed(GLFW_KEY_DOWN)) {
		forward -= 1.0;
	}

	if (keyboard.isPressed(GLFW_KEY_LEFT)) {
		sideways -= 1.0;
	}

	if (keyboard.isPressed(GLFW_KEY_RIGHT)) {
		sideways += 1.0;
	}

	const float x = static_cast<float>(dt);

	_player.moveY(forward * x);
	_player.moveX(sideways * x);
	_player.update(dt);
}

void MainState::draw() {
	_framebuffer.bindFramebuffer();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 projMatrix = glm::perspective(45.0, 4.0 / 3.0, 0.1, 100.0);

	const glm::vec3 playerPosition = _player.position();
	const glm::vec3 playerVelocity = _player.velocity();

	const glm::vec3 cameraPosition(playerPosition.x * 1.2, playerPosition.y - 3, 2);
	const glm::vec3 lightPosition(playerPosition.x, playerPosition.y - 5, 8);

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
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0, 0.0, 0.5));
	modelMatrix = glm::rotate(modelMatrix, playerVelocity.x / 12.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	mvp = projMatrix * viewMatrix * modelMatrix;
	normalMatrix = glm::inverseTranspose(viewMatrix * modelMatrix);

	_levelShader.uniform("uMVPMatrix", mvp);
	_levelShader.uniform("uNormalMatrix", normalMatrix);

	_player.render(_levelShader);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	const float offset = 0.06;
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-offset, 0.0, 0.0));
	mvp = projMatrix * viewMatrix * modelMatrix;

	_fireShader.use();
	_fireShader.uniform("uPlayerVelocity", _player.getFireStrength());
	_fireShader.uniform("uMVPMatrix", mvp);
	_fireShader.uniform("uTime", glfwGetTime());
	_player.renderFire(_fireShader);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(offset * 2, 0.0, 0.0));
	mvp = projMatrix * viewMatrix * modelMatrix;

	_fireShader.uniform("uMVPMatrix", mvp);
	_fireShader.uniform("uTime", glfwGetTime() + 1.2345678);
	_player.renderFire(_fireShader);

	_framebuffer.unbindFramebuffer();
	_framebuffer.bindTexture(0);

	_screenRenderer.render();
}
