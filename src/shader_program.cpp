#include "shader_program.hpp"
#include "logger.hpp"

ShaderProgram ShaderProgram::load(std::string basename) {
	Shader vertShader(Shader::VertexShader, basename + ".vert.glsl");
	Shader fragShader(Shader::FragmentShader, basename + ".frag.glsl");

	return ShaderProgram(vertShader, fragShader);
}

ShaderProgram::ShaderProgram(Shader &vertShader, Shader &fragShader) {
	Logger::log("Constructing ShaderProgram");

	_program = glCreateProgram();

	glAttachShader(_program, vertShader.getId());
	glAttachShader(_program, fragShader.getId());

	glLinkProgram(_program);

	int status;
	glGetProgramiv(_program, GL_LINK_STATUS, &status);

	if (status == GL_FALSE) {
		GLint log_length;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &log_length);
		GLchar *info_log = new GLchar[log_length + 1];
		glGetProgramInfoLog(_program, log_length, NULL, info_log);
		Logger::error("Linker failure:");
		Logger::error(info_log);
		delete[] info_log;

		throw "Could not link shader program";
	}
}

ShaderProgram::~ShaderProgram() {
	Logger::log("Destroying ShaderProgram");
	glDeleteProgram(_program);
}
