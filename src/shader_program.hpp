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

		ShaderProgram(std::string name, Shader& vertexShader, Shader& fragmentShader);
		~ShaderProgram();

		static ShaderProgram load(std::string basename);

		void use() const { glUseProgram(_program); };

		unsigned int getId() const {
			return _program;
		}

		void attribPointer(
			GLuint arrayBufferId,
			const std::string &name,
			GLuint size,
			GLenum type,
			GLboolean normalized,
			GLsizei stride,
			const void *pointer
		) const {
			unsigned int location = bindBuffer(name, GL_ARRAY_BUFFER, arrayBufferId);
			glVertexAttribPointer(location, size, type, normalized, stride, pointer);
		}

		void uniform(std::string name, const glm::mat4& matrix) const {
			glUniformMatrix4fv(getAttribute(name, _uniforms).location, 1, GL_FALSE, &matrix[0][0]);
		}

		void uniform(std::string name, const glm::vec3& vec3) const {
			glUniform3fv(getAttribute(name, _uniforms).location, 1, &vec3[0]);
		}

		void uniform(std::string name, double value) const {
			glUniform1f(getAttribute(name, _uniforms).location, static_cast<float>(value));
		}

		void uniform(std::string name, float value) const {
			glUniform1f(getAttribute(name, _uniforms).location, value);
		}

		void uniform(std::string name, int value) const {
			glUniform1i(getAttribute(name, _uniforms).location, value);
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
		std::string _name;
		AttributeMap _uniforms;
		AttributeMap _attributes;
		unsigned int _program;

		const Attribute& getAttribute(std::string name, const AttributeMap &attributes) const {
			if (attributes.count(name) == 0) {
				Logger::error("Could not find uniform", name, "in shader", _name);
				throw;
			}

			return attributes.at(name);
		}
};

#endif
