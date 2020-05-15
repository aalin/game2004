#include "framebuffer.hpp"
#include "opengl.hpp"
#include "logger.hpp"

Framebuffer::Framebuffer(unsigned int width, unsigned int height) {
	INFO("Creating Framebuffer", width, height);
	// Setup framebuffer
	glGenFramebuffers(1, &_framebufferId);
	bindFramebuffer();

	// Setup renderbuffer

	glGenRenderbuffers(1, &_renderbufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, _renderbufferId);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderbufferId);

	// Setup textures

	glGenTextures(2, &_textureIds[0]);

	// Setup color texture

	bindTexture(0, colorTextureId());

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTextureId(), 0);

	// Setup depth texture

	bindTexture(0, depthTextureId());

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTextureId(), 0);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		INFO("Framebuffer status is not complete");
		throw "NOT COMPLETE";
	}

	// Unbind everything
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

Framebuffer::~Framebuffer() {
	INFO("Destroying Framebuffer");
	glDeleteFramebuffers(1, &_framebufferId);
	glDeleteTextures(2, &_textureIds[0]);

	glDeleteRenderbuffers(1, &_renderbufferId);
}

void Framebuffer::bindFramebuffer() const {
	glBindFramebuffer(GL_FRAMEBUFFER, _framebufferId);
}

void Framebuffer::unbindFramebuffer() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bindTexture(unsigned int index, unsigned int id) const {
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, id);
}
