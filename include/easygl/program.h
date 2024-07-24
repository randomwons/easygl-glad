#ifndef __EASYGL_PROGRAM_H__
#define __EASYGL_PROGRAM_H__

#include <easygl/common.hpp>
#include "easygl/shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace easygl {

CLASS_PTR(Program)
class Program {
public:
    static ProgramUPtr create(const std::vector<ShaderPtr>& shaders);
    static ProgramUPtr create(const std::string& vertfile, const std::string& fragfile);
    static ProgramUPtr create(const char* vertShaderSource, const char* fragShaderSource);

    ~Program();
    uint32_t get() const { return m_program; }
    void use() const;

    void setUniform(const std::string& name, const glm::mat4& value) const;
    void setUniform(const std::string& name, const glm::vec3& value) const;
    void setUniform(const std::string& name, const glm::ivec3& value) const;
    void setUniform(const std::string& name, const glm::vec2& value) const;
    void setUniform(const std::string& name, const glm::ivec2& value) const;
    void setUniform(const std::string& name, const float value) const;
    void setUniform(const std::string& name, const int value) const;
    void setUniform3fv(const std::string& name, const void* value) const;
    void setUniform1i(const std::string& name, int value) const;

private:
    Program() {}
    bool link(const std::vector<ShaderPtr>& shaders);
    bool link(const std::string& vertfile, const std::string& fragfile);
    bool link(const char* vertShaderSource, const char* fragShaderSource);
    uint32_t m_program { 0 };

};



} // namespace easygl

#endif // __EASYGL_PROGRAM_H__