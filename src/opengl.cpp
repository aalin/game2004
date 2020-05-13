#include "opengl.hpp"
#include <iostream>
#include <string>

void _glPrintErrors(const char *file, int line) {
	GLenum error_code;

	std::string error;

	while((error_code = glGetError()) != GL_NO_ERROR) {
		switch(error_code) {
			case GL_INVALID_OPERATION:
				error = "GL_INVALID_OPERATION";
				break;
			case GL_INVALID_ENUM:
				error = "GL_INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:
				error = "GL_INVALID_VALUE";
				break;
			case GL_OUT_OF_MEMORY:
				error = "GL_OUT_OF_MEMORY";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				error = "GL_INVALID_FRAMEBUFFER_OPERATION";
				break;
		}

		std::cerr << "\e[31m" << error << " in " << file << ":" << line << "\e[0m" << std::endl;
	}
}
