#include "easygl/program.h"

namespace easygl {

ProgramUPtr Program::create(const std::vector<ShaderPtr>& shaders) {
    auto program = ProgramUPtr(new Program());
    if(!program->link(shaders))
        return nullptr;
    return std::move(program);
}

ProgramUPtr Program::create(const std::string& vertfile, const std::string& fragfile) {
    auto program = ProgramUPtr(new Program());
    if(!program->link(vertfile, fragfile))
        return nullptr;
    return std::move(program);
}

ProgramUPtr Program::create(const char* vertShaderSource, const char* fragShaderSource) {
    auto program = ProgramUPtr(new Program());
    if(!program->link(vertShaderSource, fragShaderSource))
        return nullptr;
    return std::move(program);
}


bool Program::link(const std::vector<ShaderPtr>& shaders) {
    m_program = glCreateProgram();
    for(auto& shader : shaders)
        glAttachShader(m_program, shader->get());
    glLinkProgram(m_program);

    int success = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if(!success){
        char infoLog[1024];
        glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
        printf("Failed to link program %s\n", infoLog);
        return false;
    }
    return true;
}


bool Program::link(const std::string& vertfile, const std::string& fragfile) {
    m_program = glCreateProgram();

    std::vector<ShaderPtr> shaders;
    shaders.emplace_back(Shader::createFromFile(vertfile, GL_VERTEX_SHADER));
    shaders.emplace_back(Shader::createFromFile(fragfile, GL_FRAGMENT_SHADER));

    for(auto& shader : shaders)
        glAttachShader(m_program, shader->get());
    glLinkProgram(m_program);

    int success = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if(!success){
        char infoLog[1024];
        glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
        printf("Failed to link program %s\n", infoLog);
        return false;
    }
    return true;
}

bool Program::link(const char* vertShaderSource, const char* fragShaderSource) {
    m_program = glCreateProgram();

    std::vector<ShaderPtr> shaders;
    shaders.emplace_back(Shader::createFromSource(vertShaderSource, GL_VERTEX_SHADER));
    shaders.emplace_back(Shader::createFromSource(fragShaderSource, GL_FRAGMENT_SHADER));

    for(auto& shader : shaders)
        glAttachShader(m_program, shader->get());
    glLinkProgram(m_program);

    int success = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if(!success){
        char infoLog[1024];
        glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
        printf("Failed to link program %s\n", infoLog);
        return false;
    }
    return true;
}


Program::~Program() {
    if(m_program) {
        glDeleteProgram(m_program);
    }
}

void Program::use() const {
    glUseProgram(m_program);
}

void Program::setUniform(const std::string& name, const glm::mat4& value) const {
    auto loc = glGetUniformLocation(m_program, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void Program::setUniform(const std::string& name, const glm::vec3& value) const {
    auto loc = glGetUniformLocation(m_program, name.c_str());
    glUniform3fv(loc, 1, glm::value_ptr(value));
}

void Program::setUniform(const std::string& name, const glm::ivec3& value) const {
    auto loc = glGetUniformLocation(m_program, name.c_str());
    glUniform3iv(loc, 1, glm::value_ptr(value));
}


void Program::setUniform(const std::string& name, const glm::vec2& value) const {
    auto loc = glGetUniformLocation(m_program, name.c_str());
    glUniform2fv(loc, 1, glm::value_ptr(value));
}

void Program::setUniform(const std::string& name, const glm::ivec2& value) const {
    auto loc = glGetUniformLocation(m_program, name.c_str());
    glUniform2iv(loc, 1, glm::value_ptr(value));
}

void Program::setUniform(const std::string& name, const float value) const {
    auto loc = glGetUniformLocation(m_program, name.c_str());
    glUniform1f(loc, value);
}

void Program::setUniform(const std::string& name, const int value) const {
    auto loc = glGetUniformLocation(m_program, name.c_str());
    glUniform1i(loc, value);
}

void Program::setUniform3fv(const std::string& name, const void* value) const {
    auto loc = glGetUniformLocation(m_program, name.c_str());
    glUniform3fv(loc, 1, (const GLfloat*)value);
}

void Program::setUniform1i(const std::string& name, int value) const {
    auto loc = glGetUniformLocation(m_program, name.c_str());
    glUniform1i(loc, value);
}

} // namespace easygl