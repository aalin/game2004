#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GLFW/glfw3.h>
#include <stack>

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

	private:
		static Engine* INSTANCE;

		static Engine* getInstance() {
			return INSTANCE;
		}

		GLFWwindow *_window;
		bool _running;

		void loop();

		std::stack<GameState*> _states;
};


#endif
