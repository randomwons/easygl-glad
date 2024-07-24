#include <easygl/shader.h>

namespace easygl {

ShaderUPtr Shader::createFromFile(const std::string& filename, GLenum shaderType) {

    auto shader = ShaderUPtr(new Shader());
    if(!shader->loadFile(filename, shaderType)){
        return nullptr;
    }
    return std::move(shader);

}

ShaderUPtr Shader::createFromSource(const char* source, GLenum shaderType) {

    auto shader = ShaderUPtr(new Shader());
    if(!shader->loadSource(source, shaderType)){
        return nullptr;
    }
    return std::move(shader);

}

Shader::~Shader(){
    if(m_shader){
        glDeleteShader(m_shader);
    }
}

bool Shader::loadSource(const char* source, GLenum shaderType) {
    m_shader = glCreateShader(shaderType);
    glShaderSource(m_shader, 1, &source, nullptr);
    glCompileShader(m_shader);
    int success = 0;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        char infoLog[1024];
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
        printf("reason : %s\n", infoLog);
        return false;
    }
    return true;
}

bool Shader::loadFile(const std::string& filename, GLenum shaderType) {

    auto result = loadTextFile(filename);
    if(!result.has_value()){
        return false;
    }
    auto& code = result.value();
    const char* codePtr = code.c_str();
    int32_t codeLength = (int32_t)code.length();

    m_shader = glCreateShader(shaderType);
    glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength);
    glCompileShader(m_shader);

    int success = 0;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        char infoLog[1024];
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
        printf("Failed to compile shader : '%s'\n", filename.c_str());
        printf("reason : %s\n", infoLog);
        return false;
    }
    return true;

}

} // namespace easygl