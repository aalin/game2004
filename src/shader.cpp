#include <iostream>
#include <fstream>
#include "shader.hpp"
#include "logger.hpp"

std::string readFile(std::string filename) {
	std::ifstream is(filename.c_str());

	if (is.fail()) {
		Logger::log("Could not read", filename);
		throw "Could not read the file";
	}

	is.seekg(0, std::ios::end);
	unsigned int length = is.tellg();
	is.seekg(0, std::ios::beg);

	std::string source(length, '\0');
	is.read(&source[0], length);
	is.close();

		return source;
}

Shader::Shader(ShaderType shaderType, std::string filename) {
	std::string source = readFile(filename);
	Logger::log("Shader source", filename);
	Logger::log(source);

	_shader = glCreateShader(shaderType);
	const char* data = source.c_str();
	glShaderSource(_shader, 1, &data, 0);
	glCompileShader(_shader);

	GLint status;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint logLength;
		glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &logLength);

		GLchar *info = new GLchar[logLength + 1];
		glGetShaderInfoLog(_shader, logLength, NULL, info);

		Logger::error("Errors compiling ", filename);
		Logger::error(info);

		delete[] info;

		throw "Unable to compile shader";
	}
}

Shader::~Shader() {
	std::cout << "Destructing shader " << _filename << std::endl;
	glDeleteShader(_shader);
}
