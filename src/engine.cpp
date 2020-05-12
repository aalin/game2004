#include "engine.hpp"
#include "game_state.hpp"
#include "logger.hpp"
#include <GLFW/glfw3.h>
#include <GLES2/gl2.h>
#include <iostream>

Engine* Engine::INSTANCE = 0;

void errorCallback(int error, const char* description) {
	Logger::log("Error", error);
	Logger::log("     ", description);
}

void Engine::glfwKeyCallback(GLFWwindow*, int key, int scancode, int action, int mods) {
	if (Engine::INSTANCE == 0) {
		Logger::log("Instance is 0");
		return;
	}

	INSTANCE->keyboard(key, scancode, action, mods);
}

Engine::Engine(unsigned int width, unsigned int height) {
	_running = false;

	if (Engine::getInstance() != 0) {
		throw "There is already an instance of Engine";
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	if (!glfwInit()) {
		throw "Could not initialize glfw";
	}

	glfwSetErrorCallback(errorCallback);

	_window = glfwCreateWindow(width, height, "hello", 0, 0);
	glfwSetKeyCallback(_window, &Engine::glfwKeyCallback);

	if (!_window) {
		glfwTerminate();
		throw "Could not create window";
	}

	INSTANCE = this;

	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1);
}

Engine::~Engine() {
	Logger::log("Destroying engine");

	while (!_states.empty()) {
		popState();
	}

	INSTANCE = 0;
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void Engine::start() {
	Logger::log("Starting engine");

	_running = true;

	loop();
}

void Engine::loop() {
	double lastTime = glfwGetTime();

	while (_running) {
		double currentTime = glfwGetTime();
		double delta = currentTime - lastTime;

		if (glfwWindowShouldClose(_window)) {
			_running = false;
			return;
		}

		glfwPollEvents();

		if (_states.empty()) {
			Logger::log("Stopping because there are no states");
			_running = false;
			break;
		}

		GameState* currentState = _states.top();

		currentState->update(delta);
		currentState->draw();

		glfwSwapBuffers(_window);

		lastTime = currentTime;
	}
}

void Engine::stop() {
	Logger::log("Stopping engine");
	_running = false;
}

void Engine::keyboard(int key, int scancode, int action, int mods) {
	Logger::log("Key:", key, "scancode:", scancode, "action:", action, "mods:", mods);

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		Logger::log("Escape was pressed");
		glfwSetWindowShouldClose(_window, GLFW_TRUE);
	}

	if(_states.empty())
		return;

	if(action == GLFW_PRESS)
		_states.top()->keyPress(key);
	else if(action == GLFW_RELEASE)
		_states.top()->keyRelease(key);
}

void Engine::pushState(GameState* state) {
	if(!_states.empty())
		_states.top()->pause();
	_states.push(state);
	state->setup();
}

void Engine::popState() {
	_states.pop();

	if(_states.empty())
		stop();
}
