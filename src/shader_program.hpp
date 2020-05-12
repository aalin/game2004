#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include "shader.hpp"
#include "logger.hpp"
#include <map>
#include <glm/glm.hpp>

class ShaderProgram {
	public:
		struct Attribute {
			std::string name;
			GLenum type;
			GLsizei size;
			GLuint location;
		};

		typedef std::map<std::string, Attribute> AttributeMap;

		ShaderProgram(Shader& vertexShader, Shader& fragmentShader);
		~ShaderProgram();

		static ShaderProgram load(std::string basename);

		void use() { glUseProgram(_program); }

		unsigned int getId() const {
			return _program;
		}

		void uniform(std::string name, const glm::mat4& matrix) {
			if (_uniforms.count(name) == 0) {
				Logger::error("Could not find uniform", name, "in shader");
				return;
			}

			const int location = _uniforms[name].location;

			glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
		}

	private:
		AttributeMap _uniforms;
		AttributeMap _attributes;
		unsigned int _program;
};

#endif
