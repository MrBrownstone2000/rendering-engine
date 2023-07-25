#ifndef __SHADER_HPP__
#define __SHADER_HPP__

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

            void compileShader(uint32_t shaderType, uint32_t shader);
            uint32_t loadShader(uint32_t shaderType, std::string shaderPath);
            void linkProgram(uint32_t program, uint32_t vertexShader, uint32_t fragmentShader);

            std::string preprocessShader(const std::string& shader);

        private:
            uint32_t id;

            static std::vector<std::filesystem::path> s_includeDirs;
    };
}

#endif
