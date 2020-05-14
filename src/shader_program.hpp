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

		void use() const { glUseProgram(_program); };

		unsigned int getId() const {
			return _program;
		}

		void uniform(std::string name, const glm::mat4& matrix) {
			glUniformMatrix4fv(getAttribute(name, _uniforms).location, 1, GL_FALSE, &matrix[0][0]);
		}

		void uniform(std::string name, const glm::vec3& vec3) {
			glUniform3fv(getAttribute(name, _uniforms).location, 1, &vec3[0]);
		}

		void uniform(std::string name, float value) {
			glUniform1f(getAttribute(name, _uniforms).location, value);
		}

		unsigned int bindBuffer(std::string name, GLenum type, GLint buffer) const {
			const Attribute &attribute = getAttribute(name, _attributes);

			glEnableVertexAttribArray(attribute.location);
			glBindBuffer(type, buffer);

			return attribute.location;
		}

		void disableBuffer(std::string name) const {
			const Attribute &attribute = getAttribute(name, _attributes);
			glDisableVertexAttribArray(attribute.location);
		}

	private:
		AttributeMap _uniforms;
		AttributeMap _attributes;
		unsigned int _program;

		const Attribute& getAttribute(std::string name, const AttributeMap &attributes) const {
			if (attributes.count(name) == 0) {
				Logger::error("Could not find uniform", name, "in shader");
				throw;
			}

			return attributes.at(name);
		}
};

#endif
