#include <iostream>
#include <fstream>
#include "shader_source.hpp"
#include "logger.hpp"

std::string readFile(std::string filename) {
	std::ifstream is(filename.c_str());

	if (is.fail()) {
		Logger::log("Could not read", filename);
		return "";
	}

	is.seekg(0, std::ios::end);
	unsigned int length = is.tellg();
	is.seekg(0, std::ios::beg);

	std::string source(length, '\0');
	is.read(&source[0], length);
	is.close();

		return source;
}

ShaderSource::ShaderSource(std::string filename) {
	Logger::log("shader source", filename, readFile(filename));
}

ShaderSource::~ShaderSource() {
	std::cout << "Destructing shader source " << _filename << std::endl;
}
