#ifndef SHADER_SOURCE_HPP
#define SHADER_SOURCE_HPP

#include <string>
#include "opengl.hpp"

class Shader {
	public:
		enum ShaderType {
			VertexShader = GL_VERTEX_SHADER,
			FragmentShader = GL_FRAGMENT_SHADER,
		};

		Shader(ShaderType type, std::string filename);
		~Shader();

		unsigned int getId() { return _shader; }

	private:
		std::string _filename;

		unsigned int _shader;
};

#endif
