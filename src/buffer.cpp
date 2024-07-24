#include <easygl/buffer.h>

namespace easygl {

BufferUPtr Buffer::createWithData(
    uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize) {

    auto buffer = BufferUPtr(new Buffer());
    if(!buffer->init(bufferType, usage, data, dataSize)){
        return nullptr;
    }
    return std::move(buffer);

}

BufferUPtr Buffer::create(
    uint32_t bufferType, uint32_t usage) {
    
    auto buffer = BufferUPtr(new Buffer());
    if(!buffer->init(bufferType, usage)){
        return nullptr;
    }
    return std::move(buffer);
}

Buffer::~Buffer() {
    if(m_buffer) {
        glDeleteBuffers(1, &m_buffer);
    }
}

void Buffer::bind() const {
    glBindBuffer(m_bufferType, m_buffer);
}

bool Buffer::init(uint32_t bufferType, uint32_t usage,
    const void* data, size_t dataSize) {

    m_bufferType = bufferType;
    m_usage = usage;
    glGenBuffers(1, &m_buffer);
    bind();
    glBufferData(m_bufferType, dataSize, data, usage);
    return true;

}

bool Buffer::init(uint32_t bufferType, uint32_t usage) {

    m_bufferType = bufferType;
    m_usage = usage;
    glGenBuffers(1, &m_buffer);
    bind();
    return true;

}

void Buffer::subData(const void* data, size_t dataSize) {
    bind();
    glBufferData(m_bufferType, dataSize, data, m_usage);
}

} // namespace easygl