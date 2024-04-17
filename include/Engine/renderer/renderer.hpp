#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "../gfx/vertexArray.hpp"
#include "../gfx/shader.hpp"
#include "../gfx/framebuffer.hpp"
#include "camera.hpp"
#include "mesh.hpp"
#include "model.hpp"

#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace engine::renderer
{
    void Boot();

    void beginFrame(std::shared_ptr<Framebuffer> framebuffer, std::shared_ptr<Camera> camera);
    void beginFrame(std::shared_ptr<Camera> camera);
    void endFrame();

    void submit(const std::shared_ptr<const Shader>& shader,
                const std::shared_ptr<const Texture>& texture,
                const glm::mat4& mat, const Model& model);

    void submit(const std::shared_ptr<const Shader>& shader,
                const std::shared_ptr<const Texture>& texture,
                const glm::mat4& mat, const Mesh& mesh);

    void submit(const std::shared_ptr<const Shader>& shader,
                const std::shared_ptr<const Texture>& texture,
                const glm::mat4& mat, 
                const std::shared_ptr<const VertexArray>& vao);
}

#endif
