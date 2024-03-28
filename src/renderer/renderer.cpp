#include "pch.hpp"
#include "renderer/renderer.hpp"

#include "gfx/commands.hpp"
#include <GL/glew.h>

namespace engine::renderer
{
    namespace
    {
        struct RenderItem
        {
            glm::mat4 model;
            std::shared_ptr<const Shader> shader;
            std::shared_ptr<const VertexArray> vao;
            std::shared_ptr<const Texture> texture;
        };

        struct SceneData
        {
            std::shared_ptr<Camera> camera;
        };

        std::vector<RenderItem> m_items;
        SceneData m_sceneData;

        std::shared_ptr<Framebuffer> m_default_framebuffer;
        std::shared_ptr<Framebuffer> m_current_framebuffer;
    }

    void Boot()
    {
        glEnable(GL_DEPTH_TEST);

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        m_default_framebuffer = std::make_shared<Framebuffer>();
    }

    void beginFrame(std::shared_ptr<Framebuffer> framebuffer, std::shared_ptr<Camera> camera)
    {
        framebuffer->bind();
        clear();
        m_current_framebuffer = framebuffer;
        m_sceneData.camera = camera;
    }

    void beginFrame(std::shared_ptr<Camera> camera)
    {
        beginFrame(m_default_framebuffer, camera);
    }

    void endFrame()
    {
        for (RenderItem i : m_items)
        {
            i.shader->bind();
            i.shader->setUniform("model", i.model);
            i.shader->setUniform("vp", m_sceneData.camera->getViewProjection());
            i.shader->setUniform("cameraPos", m_sceneData.camera->getPosition());
            i.shader->setUniform("cameraDir", m_sceneData.camera->getDirection());

            i.shader->bindTexture(i.texture, 0);
            i.vao->bind();
            drawIndexed(i.vao);
        }
        m_items.clear();
        m_current_framebuffer->unbind();
    }

    void submit(const std::shared_ptr<const Shader>& shader,
                const std::shared_ptr<const Texture>& texture,
                const glm::mat4& model, const Mesh& mesh)
    {
        m_items.push_back({model, shader, mesh.getVAO(), texture});
    }

    void submit(const std::shared_ptr<const Shader>& shader,
                const std::shared_ptr<const Texture>& texture,
                const glm::mat4& model, 
                const std::shared_ptr<const VertexArray>& vao)
    {
        m_items.push_back({model, shader, vao, texture});
    }
}
