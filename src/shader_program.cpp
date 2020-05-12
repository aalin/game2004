#include "shader_program.hpp"
#include "logger.hpp"

ShaderProgram::AttributeMap getAttributes(int program, GLenum attributeType) {
	int numAttributes = 0;
	glGetProgramiv(program, attributeType, &numAttributes);

	ShaderProgram::AttributeMap attributes;

	GLsizei bufSize = 32;
	GLchar name[bufSize];
	GLsizei length;

	for (GLint i = 0; i < numAttributes; i++) {
		ShaderProgram::Attribute attribute;

		switch (attributeType) {
			case GL_ACTIVE_ATTRIBUTES:
				glGetActiveAttrib(program, i, bufSize, &length, &attribute.size, &attribute.type, name);
				break;
			case GL_ACTIVE_UNIFORMS:
				glGetActiveUniform(program, i, bufSize, &length, &attribute.size, &attribute.type, name);
				break;
			default:
				throw;
		}

		attribute.location = i;
		attribute.name = std::string(name, length);

		Logger::log(attributeType, "name", attribute.name, "location", attribute.location, "size", attribute.size);
		attributes[attribute.name] = attribute;
	}

	return attributes;
}

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

	_attributes = getAttributes(_program, GL_ACTIVE_ATTRIBUTES);
	_uniforms = getAttributes(_program, GL_ACTIVE_UNIFORMS);
}

ShaderProgram::~ShaderProgram() {
	Logger::log("Destroying ShaderProgram");
	glDeleteProgram(_program);
}
