#include <iostream>
#include "logger.hpp"
#include <chrono>
#include <cstring>
#include <GLFW/glfw3.h>

std::string Logger::timestring() {
	const time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	const std::string timestr = std::string(std::ctime(&currentTime));
	return timestr.substr(0, timestr.length() - 1);
}

double Logger::getTime() {
	return glfwGetTime();
}
