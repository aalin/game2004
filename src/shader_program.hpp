#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include "shader.hpp"
#include "logger.hpp"
#include <map>
#include <glm/glm.hpp>

class ShaderProgram {
	public:
		ShaderProgram(Shader& vertexShader, Shader& fragmentShader);
		~ShaderProgram();

		static ShaderProgram load(std::string basename);

		void use() { glUseProgram(_program); }

		unsigned int getId() const {
			return _program;
		}

		void uniform(std::string name, const glm::mat4& matrix) {
			if (_uniformLocations.count(name) == 0) {
				Logger::error("Could not find uniform", name, "in shader");
				return;
			}

			const int location = _uniformLocations[name];
			glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
		}

	private:
		std::map<std::string, int> _uniformLocations;
		unsigned int _program;
};

#endif
