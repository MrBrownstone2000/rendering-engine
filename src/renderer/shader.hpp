#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace engine::renderer
{
    class Shader
    {
        public:
            GLuint id; // Program ID

            // Reads and builds the shader program
            Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
            Shader();

            Shader(const Shader& rhs) = delete;
            Shader(Shader&& rhs);
            Shader& operator=(const Shader& rhs) = delete;
            Shader& operator=(Shader&& rhs);
            ~Shader();

            // Activate / Use the program
            void use() const;

            // Uniform utility function
            void setUniform(const std::string &name, bool value) const;
            void setUniform(const std::string &name, int value) const;
            void setUniform(const std::string &name, float value) const;
            void setUniform(const std::string &name, float v1, float v2, float v3, float v4) const;
            void setUniform(const std::string &name, const glm::mat4& value) const;
            void setUniform(const std::string &name, const glm::mat3& value) const;
            void setUniform(const std::string &name, const glm::vec3& value) const;
            void setUniform(const std::string &name, const glm::vec4& value) const;

            static void setBaseDir(const std::string dir);

        private:
            std::string readFile(std::string fileName);

            void compileShader(GLuint shaderType, GLuint shader);
            GLuint loadShader(GLuint shaderType, std::string shaderPath);
            void linkProgram(GLuint program, GLuint vertexShader, GLuint fragmentShader);

            std::string preprocessShader(const std::string& shader);

        private:
            static std::string s_baseDir;
    };
}

#endif
