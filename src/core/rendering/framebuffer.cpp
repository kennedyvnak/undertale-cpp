#include "enpch.h"
#include "framebuffer.h"
#include "texture.h"

namespace engine {
    Framebuffer::Framebuffer(int width, int height) {
        glGenFramebuffers(1, &_id);
        bind();

        _texture = create_scope<Texture>(width, height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->get_id(), 0);

        unsigned int rbo_id;
        glGenRenderbuffers(1, &rbo_id);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo_id);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo_id);

        EN_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "FrameBuffer isn't complete.");
        unbind();
    }

    Framebuffer::~Framebuffer() {
        glDeleteFramebuffers(1, &_id);
    }

    void Framebuffer::bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, _id);
    }

    void Framebuffer::unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}