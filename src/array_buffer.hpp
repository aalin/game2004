#ifndef ARRAY_BUFFER_HPP
#define ARRAY_BUFFER_HPP

#include "opengl.hpp"
#include "shader_program.hpp"
#include "logger.hpp"
#include <vector>

class ArrayBuffer {
	public:
		template<typename V>
		ArrayBuffer(const std::vector<V>& vertices) {
			glGenBuffers(1, &_arrayBufferId);
			glBindBuffer(GL_ARRAY_BUFFER, _arrayBufferId);
			_vertexSize = sizeof(V) / sizeof(float);
			Logger::log("Constructing ArrayBuffer with", vertices.size(), "vertices of size", _vertexSize, "total bytes:", vertices.size() * sizeof(V));
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(V), &vertices[0], GL_STATIC_DRAW);
		}

		~ArrayBuffer() {
			Logger::error("Destroying ArrayBuffer", _arrayBufferId);
			glDeleteBuffers(1, &_arrayBufferId);
		}

		void disable(const ShaderProgram &shaderProgram, const std::string &name) const {
			shaderProgram.disableBuffer(name);
		}

		void attribPointer(const ShaderProgram &shaderProgram, const std::string &name) const {
			unsigned int location = shaderProgram.bindBuffer(name, GL_ARRAY_BUFFER, _arrayBufferId);

			// Logger::log("Binding", name, "to", location, "size:", _vertexSize);

			glVertexAttribPointer(
				location,
				_vertexSize,
				GL_FLOAT,
				GL_FALSE,
				0,
				0
			);
		}

	private:
		GLuint _arrayBufferId;
		GLenum _mode;
		unsigned int _vertexSize;
};

#endif
