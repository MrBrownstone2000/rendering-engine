#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "../gfx/vertexArray.hpp"
#include "../gfx/shader.hpp"
#include "camera.hpp"
#include "mesh.hpp"

#include <memory>
#include <vector>

namespace engine::renderer
{
    void beginFrame(const Camera& camera);
    void endFrame();
    void submit(const std::shared_ptr<Shader>& shader, const Mesh& mesh);
    void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<const VertexArray>& vao);
}

#endif
