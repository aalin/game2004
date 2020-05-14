#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "logger.hpp"
#include <map>

class Keyboard {
	public:
		void handlePress(int key, int scancode, int mods) {
			Logger::log("handlePress key:", key, "scancode:", scancode, "mods:", mods);
			_keyStates[key] = { scancode, mods };
		}

		void handleRelease(int key) {
			Logger::log("handleRelease key:", key);
			_keyStates.erase(key);
		}

		bool isPressed(int key) const {
			return _keyStates.count(key) == 1;
		}

	private:
		struct KeyState {
			int scancode;
			int mods;
		};

		std::map<int, KeyState> _keyStates;
};

#endif
