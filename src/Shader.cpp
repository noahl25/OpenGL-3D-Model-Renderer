#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Debug.h"

Shader::Shader(const std::string& file)
    : m_FilePath(file), m_RendererID(0)
{
    auto source = ParseShader(file);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

ShadersProgramSource Shader::ParseShader(const std::string& file) {

    std::fstream stream(file);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };


    ShaderType type = ShaderType::NONE;
    std::stringstream ss[2];

    std::string line;
    while (getline(stream, line)) {

        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {

            if (type == ShaderType::NONE) {
                std::cout << "Shader parsing failed, specify shader with #shader \"shader type\"" << std::endl;
                return {};
            }

            ss[(int)type] << line << '\n';
          
        }

    }

    if (type == ShaderType::NONE) {
        std::cout << "Shader parsing failed, specify shader with #shader \"shader type\"" << std::endl;
    }

    return { ss[0].str(), ss[1].str() };

}


unsigned Shader::CompileShader(unsigned type, const std::string& source) {

    unsigned id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader:";
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;

    }

    return id;

}

unsigned Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {

    unsigned program = glCreateProgram();

    unsigned vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}



void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, glm::vec4 value)
{
    glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.contains(name)) {
        return m_UniformLocationCache[name];
    }

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
        std::cout << "uniform " << name << " is nonexistent" << std::endl;

    m_UniformLocationCache[name] = location;

    return location;
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}