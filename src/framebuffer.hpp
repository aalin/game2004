#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "opengl.hpp"

class Framebuffer {
	public:
		Framebuffer(unsigned int width, unsigned int height, unsigned int textureIndex);
		~Framebuffer();

		void bindFramebuffer() const;
		void unbindFramebuffer() const;
		void bindTexture(unsigned int texture) const;

	private:
		GLuint _textureId;
		GLuint _renderbufferId;
		GLuint _framebufferId;
};

#endif
