#include "pch.hpp"
#include "renderer.hpp"

#include "../gfx/commands.hpp"
#include <GL/glew.h>

namespace engine::renderer
{
    void Boot()
    {
        glEnable(GL_DEPTH_TEST);
    }

    namespace
    {
        struct RenderItem
        {
            glm::mat4 model;
            std::shared_ptr<const Shader> shader;
            std::shared_ptr<const VertexArray> vao;
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
            i.shader->setUniform("model", i.model);
            i.shader->setUniform("vp", m_sceneData.projection * m_sceneData.view);
            i.shader->setUniform("cameraPos", m_sceneData.position);
            i.shader->setUniform("cameraDir", m_sceneData.direction);

            i.vao->bind();
            drawIndexed(i.vao);
        }
        m_items.clear();
    }

    void submit(const glm::mat4& model, const std::shared_ptr<const Shader>& shader, const Mesh& mesh)
    {
        m_items.push_back({model, shader, mesh.getVAO()});
    }

    void submit(const glm::mat4& model, const std::shared_ptr<const Shader>& shader, const std::shared_ptr<const VertexArray>& vao)
    {
        m_items.push_back({model, shader, vao});
    }
}
