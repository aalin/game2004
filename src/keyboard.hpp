#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "logger.hpp"
#include <map>

class Keyboard {
	public:
		void handlePress(int key, int scancode, int mods) {
			Logger::log("handlePress key:", key, "scancode:", scancode, "mods:", mods);
			_keyStates[key] = { scancode, mods };
			_recentlyPressed[key] = true;
		}

		void handleRelease(int key) {
			Logger::log("handleRelease key:", key);
			_keyStates.erase(key);
		}

		bool isPressed(int key) const {
			return _keyStates.count(key) == 1;
		}

		bool wasJustPressed(int key) const {
			return _recentlyPressed.count(key) == 1;
		}

		void update() {
			_recentlyPressed.clear();
		}

	private:
		struct KeyState {
			int scancode;
			int mods;
		};

		std::map<int, KeyState> _keyStates;
		std::map<int, bool> _recentlyPressed;
};

#endif
