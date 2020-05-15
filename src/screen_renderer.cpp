#include "screen_renderer.hpp"
#include "logger.hpp"

#include <iostream>

const float vertices[] = {
	// Verts,      Texcoords
	 1.0, 1.0,     1.0, 1.0,
	-1.0, 1.0,     0.0, 1.0,
	 1.0,-1.0,     1.0, 0.0,
	-1.0,-1.0,     0.0, 0.0,
};

ScreenRenderer::ScreenRenderer() : _shaderProgram(ShaderProgram::load("shaders/screen")) {
	glGenBuffers(1, &_arrayBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, _arrayBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

ScreenRenderer::~ScreenRenderer() {
	glDeleteBuffers(1, &_arrayBufferId);
}

void ScreenRenderer::render() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 800, 600);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaderProgram.use();

	_shaderProgram.uniform("uTexture", 0);
	_shaderProgram.uniform("uColorTexture", true);

	glBindBuffer(GL_ARRAY_BUFFER, _arrayBufferId);

	const float size = sizeof(float) * 4;

	_shaderProgram.attribPointer(_arrayBufferId, "aPosition", 2, GL_FLOAT, GL_FALSE, size, reinterpret_cast<void*>(sizeof(float) * 0));
	_shaderProgram.attribPointer(_arrayBufferId, "aTexCoords", 2, GL_FLOAT, GL_FALSE, size, reinterpret_cast<void*>(sizeof(float) * 2));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
