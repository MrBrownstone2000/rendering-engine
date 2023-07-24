#include "pch.hpp"
#include "renderer.hpp"

#include "commands.hpp"

namespace engine::renderer
{
    namespace
    {
        struct RenderItem
        {
            std::shared_ptr<Shader> shader;
            std::shared_ptr<VertexArray> vao;
        };

        struct SceneData
        {
            glm::mat4 view;
            glm::mat4 projection;
            glm::vec3 position;
            glm::vec3 direction;
        };

        std::vector<RenderItem> m_items;
        SceneData m_sceneData;
    }


    void beginFrame(const Camera& camera)
    {
        clear();
        m_sceneData.view = camera.view();
        m_sceneData.projection = camera.projection();
        m_sceneData.position = camera.position();
        m_sceneData.direction = camera.direction();
    }

    void endFrame()
    {
        for (RenderItem i : m_items)
        {
            i.shader->bind();
            i.shader->setUniform("view", m_sceneData.view);
            i.shader->setUniform("projection", m_sceneData.projection);
            i.shader->setUniform("cameraPos", m_sceneData.position);
            i.shader->setUniform("cameraDir", m_sceneData.direction);

            i.vao->bind();
            drawIndexed(i.vao);
        }
    }

    void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vao)
    {
        m_items.push_back({shader, vao});
    }
}
