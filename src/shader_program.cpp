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
		GLint logLength;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &logLength);
		GLchar *infoLog = new GLchar[logLength + 1];
		glGetProgramInfoLog(_program, logLength, NULL, infoLog);
		Logger::error("Linker failure:");
		Logger::error(infoLog);
		delete[] infoLog;

		throw "Could not link shader program";
	}

	int numUniforms = 0;
	glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &numUniforms);

	for (GLint i = 0; i < numUniforms; i++) {
		GLint size;
		GLenum type;
		GLsizei bufSize = 32;
		GLchar name[bufSize];
		GLsizei length;

		glGetActiveUniform(_program, i, bufSize, &length, &size, &type, name);
		const std::string sname = std::string(name, length);

		Logger::log("name", sname, "position", i, "length", length);
		_uniformLocations[sname] = i;
	}
}

ShaderProgram::~ShaderProgram() {
	Logger::log("Destroying ShaderProgram");
	glDeleteProgram(_program);
}
