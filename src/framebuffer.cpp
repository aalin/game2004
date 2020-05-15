#include "framebuffer.hpp"
#include "opengl.hpp"
#include "logger.hpp"

constexpr bool COLOR_TEXTURE = true;

Framebuffer::Framebuffer(unsigned int width, unsigned int height, unsigned int textureIndex) {
	INFO("Creating Framebuffer", width, height);

	// Setup texture
	glGenTextures(1, &_textureId);
	bindTexture(textureIndex);

	if (COLOR_TEXTURE) {
		INFO("Making a color texture");
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	} else {
		INFO("Making a depth texture");
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Setup renderbuffer

	if (COLOR_TEXTURE) {
		glGenRenderbuffers(1, &_renderbufferId);
		glBindRenderbuffer(GL_RENDERBUFFER, _renderbufferId);

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	}

	// Setup framebuffer
	glGenFramebuffers(1, &_framebufferId);
	bindFramebuffer();

	if (COLOR_TEXTURE) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureId, 0);
	} else {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _textureId, 0);
	}

	if (COLOR_TEXTURE) {
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderbufferId);
	}

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		INFO("Framebuffer status is not complete");
		throw "NOT COMPLETE";
	}

	// Unbind everything
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (COLOR_TEXTURE) {
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}

Framebuffer::~Framebuffer() {
	INFO("Destroying Framebuffer");
	glDeleteFramebuffers(1, &_framebufferId);
	glDeleteTextures(1, &_textureId);

	if (COLOR_TEXTURE) {
		glDeleteRenderbuffers(1, &_renderbufferId);
	}
}

void Framebuffer::bindFramebuffer() const {
	glBindFramebuffer(GL_FRAMEBUFFER, _framebufferId);
}

void Framebuffer::unbindFramebuffer() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bindTexture(unsigned int index) const {
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, _textureId);
}
