#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <filesystem>

namespace engine::renderer
{
    class Shader
    {
        public:
            // Reads and builds the shader program
            Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
            Shader();

            Shader(const Shader& rhs) = delete;
            Shader(Shader&& rhs);
            Shader& operator=(const Shader& rhs) = delete;
            Shader& operator=(Shader&& rhs);
            ~Shader();

            void bind() const;
            void unbind() const;

            // Uniform utility function
            void setUniform(const std::string &name, bool value) const;
            void setUniform(const std::string &name, int value) const;
            void setUniform(const std::string &name, float value) const;
            void setUniform(const std::string &name, float v1, float v2, float v3, float v4) const;
            void setUniform(const std::string &name, const glm::mat4& value) const;
            void setUniform(const std::string &name, const glm::mat3& value) const;
            void setUniform(const std::string &name, const glm::vec3& value) const;
            void setUniform(const std::string &name, const glm::vec4& value) const;

            static void setIncludeDirs(const std::vector<std::filesystem::path>& dirs);

        private:
            std::string readFile(std::string fileName);

            void compileShader(GLuint shaderType, GLuint shader);
            GLuint loadShader(GLuint shaderType, std::string shaderPath);
            void linkProgram(GLuint program, GLuint vertexShader, GLuint fragmentShader);

            std::string preprocessShader(const std::string& shader);

        private:
            GLuint id; // Program ID

            static std::vector<std::filesystem::path> s_includeDirs;
    };
}

#endif
