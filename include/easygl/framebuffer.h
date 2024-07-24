#ifndef __EASYGL_FRAMEBUFFER_H__
#define __EASYGL_FRAMEBUFFER_H__

#include <easygl/common.hpp>

namespace easygl {

CLASS_PTR(FrameBuffer)
class FrameBuffer {
public:
    static FrameBufferUPtr create();
    ~FrameBuffer();
    void attachTexture(GLenum attachment, GLenum internalFormat, GLenum format, GLenum type, GLsizei width, GLsizei height, GLint level = 0);
    void attachRenderBuffer(GLenum attachment, GLenum internalFormat, GLsizei width, GLsizei height);
    void setDrawBuffers(int n, GLuint* attachments);

    void bind() const { glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer); }
    void unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    GLuint getTexture(int index = 0) {
        if(index < m_textures.size()) return m_textures[index];
        else return m_textures[0];
    }
    
    bool complete() const;

private:
    FrameBuffer() {};
    bool init();

    GLuint m_framebuffer;
    std::vector<GLuint> m_textures;
    std::vector<GLuint> m_renderbuffers;    


};

} // namespace easygl

#endif // __EASYGL_FRAMEBUFFER_H__