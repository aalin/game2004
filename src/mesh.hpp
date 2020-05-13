#ifndef MESH_HPP
#define MESH_HPP

#include "array_buffer.hpp"
#include <memory>

class Mesh {
	public:
		enum struct PrimitiveType {
			Points = GL_POINTS,
			Lines = GL_LINES,
			TriangleStrip = GL_TRIANGLE_STRIP,
			Triangles = GL_TRIANGLES
		};

		Mesh(GLenum primitiveType) {
			//_mode = static_cast<GLenum>(primitiveType);
			_mode = primitiveType;
			_size = 0;
		}

		template<typename V>
		void addBuffer(std::string name, const std::vector<V>& vertices) {
			const unsigned int size = vertices.size();

			if (size == 0) {
				throw "Size is 0";
			} else if (_size > 0 && size != _size) {
				Logger::error("Size", size, "is different from", _size);
				throw "Size is different";
			} else {
				_size = size;
			}

			_arrayBuffers[name] = std::make_shared<ArrayBuffer>(vertices);

		}

		void render(const ShaderProgram &shaderProgram) {
			shaderProgram.use();

			for (const auto &entry : _arrayBuffers) {
				entry.second->attribPointer(shaderProgram, entry.first);
			}

			Logger::log("Drawing arrays, size:", _size);

			glDrawArrays(_mode, 0, _size);

			for (const auto &entry : _arrayBuffers) {
				entry.second->disable(shaderProgram, entry.first);
			}
		}

	private:
		std::map<std::string, std::shared_ptr<ArrayBuffer> > _arrayBuffers;
		unsigned int _size;
		GLenum _mode;
};

#endif
