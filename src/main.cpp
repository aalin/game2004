#include "engine.hpp"
#include "main_state.hpp"

int main() {
	Engine engine(800, 600);

	engine.pushState(new MainState(engine));
	engine.start();

	return 0;
}
