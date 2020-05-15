#ifndef SCREEN_RENDERER_HPP
#define SCREEN_RENDERER_HPP

#include "opengl.hpp"
#include "shader_program.hpp"

class ScreenRenderer {
	public:
		ScreenRenderer();
		~ScreenRenderer();

		void render() const;

	private:
		ShaderProgram _shaderProgram;
		GLuint _arrayBufferId;
};

#endif
