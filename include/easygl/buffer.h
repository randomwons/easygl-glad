#ifndef __EASYGL_BUFFER_H__
#define __EASYGL_BUFFER_H__

#include <easygl/common.hpp>

namespace easygl {

CLASS_PTR(Buffer)
class Buffer {
public:
    static BufferUPtr createWithData(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize);
    static BufferUPtr create(uint32_t bufferType, uint32_t usage);
    ~Buffer();

    uint32_t get() const { return m_buffer; }
    void bind() const;
    void unbind() const { glBindBuffer(m_bufferType, 0); }
    void subData(const void* data, size_t dataSize);

private:
    Buffer() {}
    bool init(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize);
    bool init(uint32_t bufferType, uint32_t usage);

    uint32_t m_buffer { 0 };
    uint32_t m_bufferType { 0 };
    uint32_t m_usage { 0 };

};

} // namespace easygl

#endif // __EASYGL_BUFFER_H__