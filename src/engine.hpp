#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GLFW/glfw3.h>
#include <stack>
#include "keyboard.hpp"

class GameState;

class Engine {
	public:
		Engine(unsigned int width, unsigned int height);
		~Engine();

		void start();
		void stop();

		void pushState(GameState*);
		void popState();

		static void glfwKeyCallback(GLFWwindow*, int key, int scancode, int action, int mods);

		void keyboard(int key, int scancode, int action, int mods);

		unsigned int width() const {
			return _width;
		}

		unsigned int height() const {
			return _height;
		}

	private:
		static Engine* INSTANCE;

		static Engine* getInstance() {
			return INSTANCE;
		}

		const unsigned int _width;
		const unsigned int _height;

		GLFWwindow *_window;
		bool _running;

		void loop();

		std::stack<GameState*> _states;

		Keyboard _keyboard;
};


#endif
