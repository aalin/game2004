#include "engine.hpp"
#include "main_state.hpp"
#include "logger.hpp"
#include <iostream>

int main() {
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	if (!glfwInit()) {
		std::cerr << "Could not initialize glfw" << std::endl;
		return 1;
	}

	try {
		Engine engine(800, 600);

		engine.pushState(new MainState(engine));
		engine.start();
	} catch (const char* msg) {
		Logger::error("Main caught exception:", msg);
		glfwTerminate();
		return 1;
	}

	glfwTerminate();

	return 0;
}
