#ifndef __SHADER_H__
#define __SHADER_H__

#include "easygl/easygl.hpp"

namespace easygl {

CLASS_PTR(Shader)
class Shader {
public:
    static ShaderUPtr createFromFile(const std::string& filename, GLenum shaderType);
    static ShaderUPtr createFromSource(const char* source, GLenum shaderType);
    ~Shader();

    uint32_t get() const { return m_shader; }

private:
    Shader() {}
    bool loadFile(const std::string& filename, GLenum shaderType);
    bool loadSource(const char* source, GLenum shaderType);
    uint32_t m_shader { 0 };

};

} // namespace easygl

#endif // __SHADER_H__