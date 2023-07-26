#include "pch.hpp"
#include "shader.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

namespace engine::renderer
{
    std::vector<std::filesystem::path> Shader::s_includeDirs;

    void Shader::setIncludeDirs(const std::vector<std::filesystem::path>& dirs)
    {
        s_includeDirs = dirs;
    }

    // Reads and builds the shader program
    Shader::Shader(const std::filesystem::path &vertexShaderPath, const std::filesystem::path &fragmentShaderPath)
    {
        uint32_t vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderPath);
        uint32_t fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

        // Link shader program
        m_id = glCreateProgram();
        linkProgram(m_id, vertexShader, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::Shader()
        : m_id(0)
    {
    }

    Shader::Shader(Shader &&rhs)
    {
        m_id = rhs.m_id;
        rhs.m_id = 0;
    }

    Shader &Shader::operator=(Shader &&rhs)
    {
        glDeleteProgram(m_id);
        m_id = rhs.m_id;
        rhs.m_id = 0;

        return *this;
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_id);
    }

    void Shader::bind() const
    {
        glUseProgram(m_id);
    }

    void Shader::unbind() const
    {
        glUseProgram(0);
    }

    // Uniform utility functions
    void Shader::setUniform(const std::string &name, bool value) const
    {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        glUniform1i(location, static_cast<int>(value));
    }
    void Shader::setUniform(const std::string &name, int value) const
    {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        glUniform1i(location, value);
    }
    void Shader::setUniform(const std::string &name, float value) const
    {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        glUniform1f(location, value);
    }
    void Shader::setUniform(const std::string &name, float v1, float v2, float v3, float v4) const
    {
        GLint location = glGetUniformLocation(m_id, name.c_str());

        glUniform4f(location, v1, v2, v3, v4);
    }
    void Shader::setUniform(const std::string &name, const glm::mat4 &value) const
    {
        uint32_t location = glGetUniformLocation(m_id, name.c_str());

        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
    void Shader::setUniform(const std::string &name, const glm::mat3 &value) const
    {
        uint32_t location = glGetUniformLocation(m_id, name.c_str());

        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
    void Shader::setUniform(const std::string &name, const glm::vec3 &value) const
    {
        uint32_t location = glGetUniformLocation(m_id, name.c_str());

        glUniform3f(location, value.x, value.y, value.z);
    }
    void Shader::setUniform(const std::string &name, const glm::vec4 &value) const
    {
        uint32_t location = glGetUniformLocation(m_id, name.c_str());

        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    // ============================= Utility functions =============================

    std::string Shader::readFile(std::filesystem::path fileName)
    {
        std::ifstream file;
        std::string content;

        std::filesystem::path dir;
        for (const auto& dir : s_includeDirs)
        {
            file.open(dir / fileName);
            if (file) break; 
        } 

        if (!file) engineLog.error("Cannot find shader " + fileName.string());

        content = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

        return content;
    }

    void Shader::compileShader(uint32_t shaderType, uint32_t shader)
    {
        glCompileShader(shader);

        int success = true;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::string type;
            switch (shaderType)
            {
                case GL_VERTEX_SHADER:
                    type = "VERTEX";
                    break;
                case GL_FRAGMENT_SHADER:
                    type = "FRAGMENT";
                    break;
            }
            std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED" << std::endl
                << infoLog << std::endl;
            exit(1);
        }
    }

    uint32_t Shader::loadShader(uint32_t shaderType, std::filesystem::path shaderPath)
    {
        std::string source = readFile(shaderPath);

        source = preprocessShader(source);

        const char *vertexShaderSource = source.c_str();

        uint32_t shader;
        shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &vertexShaderSource, nullptr);
        compileShader(shaderType, shader);
        return shader;
    }

    void Shader::linkProgram(uint32_t program, uint32_t vertexShader, uint32_t fragmentShader)
    {
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        int success = true;
        char infoLog[512];
        glGetShaderiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(program, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl
                << infoLog << std::endl;
            exit(1);
        }
    }

    std::string Shader::preprocessShader(const std::string &shader)
    {
        std::string out;
        std::istringstream is(shader);
        std::string line;

        while (std::getline(is, line))
        {
            if (line.find("#include") != 0)
            {
                out += line + '\n';
            }
            else
            {
                int start = line.find('"');
                int end = line.find('"', start + 1);
                std::string file = line.substr(start + 1, end - start - 1);
                std::string include = readFile(file);
                include = preprocessShader(include);
                out += include;
            }
        }
        return out;
    }
}

