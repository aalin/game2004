#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "opengl.hpp"

class Framebuffer {
	public:
		Framebuffer(unsigned int width, unsigned int height);
		~Framebuffer();

		void bindFramebuffer() const;
		void unbindFramebuffer() const;
		void bindTexture(unsigned int texture, unsigned int index) const;

		const GLuint& colorTextureId() const { return _textureIds[0]; }
		const GLuint& depthTextureId() const { return _textureIds[1]; }

	private:
		GLuint _textureIds[2];
		GLuint _renderbufferId;
		GLuint _framebufferId;
};

#endif
