#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "vertexArray.hpp"
#include "shader.hpp"

#include <memory>
#include <vector>

namespace engine::renderer
{
    class Renderer
    {
        public:
            static void beginFrame();
            static void endFrame();
            static void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vao);

        private:
            struct RenderItem
            {
                std::shared_ptr<Shader> shader;
                std::shared_ptr<VertexArray> vao;
            };

        private:
            static std::vector<RenderItem> m_items;
    };
}

#endif
