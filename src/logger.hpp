#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <sstream>
#include <string>
#include <iostream>

namespace Logger {
	std::string timestring();
	double getTime();

	template<typename V>
	std::string valueColor(V) {
		return "\e[0m";
	}

	inline std::string valueColor(const char*) { return "\e[32m"; }
	inline std::string valueColor(std::string) { return "\e[32m"; }
	inline std::string valueColor(int) { return "\e[33m"; }
	inline std::string valueColor(float) { return "\e[33m"; }
	inline std::string valueColor(double) { return "\e[33m"; }

	template <typename V>
	inline void writeValue(std::ostringstream& oss, const V value, bool isLast = false) {
		oss << valueColor(value);
		oss << value;

		if (!isLast) {
			oss << " ";
		}
	}

	inline void logStringAppend(std::ostringstream&) { }

	template <typename V>
	inline void logStringAppend(std::ostringstream& oss, const V value) {
		oss << valueColor(value);
		oss << value;
	}

	template <typename V, typename ...A>
	inline void logStringAppend(std::ostringstream& oss, const V value, const A... args) {
		oss << valueColor(value);
		oss << value << " ";
		logStringAppend(oss, args...);
	}

	template <typename ...A>
	inline std::string logString(const A ...args) {
		std::ostringstream oss;
		logStringAppend(oss, args...);
		return oss.str();
	}

	template <typename ...A>
	inline void log(const A ...args) {
		std::cout << timestring() << ": " << logString(args...) << "\e[0m" << std::endl;
	}

	template <typename ...A>
	inline void logLocation(const char *file, int line, const A ...args) {
		std::cout << timestring() << ": " << file << ":" << line << ": " << logString(args...) << "\e[0m" << std::endl;
	}

	template <typename ...A>
	inline void error(const A ...args) {
		std::cerr << "\e[31m" << timestring() << ": " << logString(args...) << "\e[0m" << std::endl;
	}

	template <typename ...A>
	inline void warn(const A ...args) {
		std::cerr << "\e[33m" << timestring() << ": " << logString(args...) << "\e[0m" << std::endl;
	}
};

#define INFO(...) Logger::logLocation(__FILE__, __LINE__, __VA_ARGS__)

#endif
