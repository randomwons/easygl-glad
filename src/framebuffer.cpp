#include <easygl/framebuffer.h>

namespace easygl {

FrameBufferUPtr FrameBuffer::create() {
    FrameBufferUPtr frameBuffer(new FrameBuffer());
    if (!frameBuffer->init()) {
        return nullptr;
    }
    return std::move(frameBuffer);
}

FrameBuffer::~FrameBuffer() {
    if (m_framebuffer) {
        glDeleteFramebuffers(1, &m_framebuffer);
    }
    if (!m_textures.empty()) {
        glDeleteTextures(m_textures.size(), m_textures.data());
    }
    if (!m_renderbuffers.empty()) {
        glDeleteRenderbuffers(m_renderbuffers.size(), m_renderbuffers.data());
    }
}

bool FrameBuffer::init() {
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

void FrameBuffer::attachTexture(GLenum attachment, GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height, GLint level) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, height, 0, format, type, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture, level);

    m_textures.push_back(texture);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void FrameBuffer::attachRenderBuffer(GLenum attachment, GLenum internalFormat, GLsizei width, GLsizei height) {
    GLuint renderbuffer;
    glGenRenderbuffers(1, &renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);

    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderbuffer);

    m_renderbuffers.push_back(renderbuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void FrameBuffer::setDrawBuffers(int n, GLuint* attachments) {
    glDrawBuffers(n, attachments);
}

bool FrameBuffer::complete() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return status == GL_FRAMEBUFFER_COMPLETE;
}

} // namespace easygl