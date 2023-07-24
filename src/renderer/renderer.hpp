#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "vertexArray.hpp"
#include "shader.hpp"
#include "camera.hpp"

#include <memory>
#include <vector>

namespace engine::renderer
{
    void beginFrame(const Camera& camera);
    void endFrame();
    void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vao);
}

#endif
