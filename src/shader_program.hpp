#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include "shader.hpp"
#include <map>

class ShaderProgram {
	public:
		ShaderProgram(Shader& vertexShader, Shader& fragmentShader);
		~ShaderProgram();

		static ShaderProgram load(std::string basename);

		unsigned int getId() const {
			return _program;
		}

	private:
		std::map<std::string, int> _uniformLocations;
		unsigned int _program;
};

#endif
