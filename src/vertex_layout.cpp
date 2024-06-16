#include "easygl/vertex_layout.h"

namespace easygl {

VertexLayoutUPtr VertexLayout::create() {

    auto vertexLayout = VertexLayoutUPtr(new VertexLayout());
    vertexLayout->init();
    return std::move(vertexLayout);

}

VertexLayout::~VertexLayout() {
    if(m_vao) {
        glDeleteVertexArrays(1, &m_vao);
    }
}

void VertexLayout::bind() const {
    glBindVertexArray(m_vao);
}

void VertexLayout::setAttrib(
    uint32_t attribIndex, int count,
    uint32_t type, bool normalized,
    size_t stride, uint64_t offset) const {

    bind();
    glEnableVertexAttribArray(attribIndex);
    glVertexAttribPointer(attribIndex, count,
        type, normalized, stride, (const void*)offset);
}

void VertexLayout::setAttribDivisor(uint32_t attribIndex) const {
    bind();
    glVertexAttribDivisor(attribIndex, 1);
}

void VertexLayout::init() {
    glGenVertexArrays(1, &m_vao);
    bind();
}

} // namespace easygl