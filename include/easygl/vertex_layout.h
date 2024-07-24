#ifndef __EASYGL_VL_H__
#define __EASYGL_VL_H__

#include <easygl/common.hpp>

namespace easygl {

CLASS_PTR(VertexLayout)
class VertexLayout {
public:
    static VertexLayoutUPtr create();
    ~VertexLayout();

    uint32_t get() const { return m_vao; }
    void bind() const;
    void unbind() const { glBindVertexArray(0); }
    void setAttrib(
        uint32_t attribIndex, int count,
        uint32_t type, bool normalized,
        size_t stride, uint64_t offset) const;
    // void disableAttrib(int attribIndex) const;
    void setAttribDivisor(uint32_t attribIndex) const;

private:
    VertexLayout() {}
    void init();

    uint32_t m_vao { 0 };
};

} // namespace easygl

#endif // __EASYGL_VL_H__