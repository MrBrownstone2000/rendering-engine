#include "pch.hpp"
#include "renderer.hpp"

#include "commands.hpp"

namespace engine::renderer
{
    std::vector<Renderer::RenderItem> Renderer::m_items;

    void Renderer::beginFrame()
    {
        clear();
    }

    void Renderer::endFrame()
    {
        for (RenderItem i : m_items)
        {
            i.shader->bind();
            i.vao->bind();
            drawIndexed(i.vao);
        }
    }

    void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vao)
    {
        m_items.push_back({shader, vao});
    }
}
