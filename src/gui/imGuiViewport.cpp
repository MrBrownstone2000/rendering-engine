#include "pch.hpp"
#include "gui/imGuiViewport.hpp"
#include "imgui.h"
#include "core/app.hpp"
#include "events/viewportEvent.hpp"

#include <GL/glew.h>

namespace engine
{
    ImGuiViewport::ImGuiViewport(std::shared_ptr<Framebuffer> framebuffer)
        : m_framebuffer(framebuffer), m_isFocused(false), m_isHovered(false)
    {
    }

    const std::shared_ptr<Framebuffer> ImGuiViewport::getFramebuffer() const
    {
        return m_framebuffer;
    }

    bool ImGuiViewport::isFocused() const
    {
        return m_isFocused;
    }

    bool ImGuiViewport::isHovered() const
    {
        return m_isHovered;
    }

    void ImGuiViewport::setEventCallback(const EventCallback& cb)
    {
        m_eventCallback = cb;
    }

    void ImGuiViewport::onImGuiRender()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Scene");

        m_isFocused = ImGui::IsWindowFocused();
        m_isHovered = ImGui::IsWindowHovered();
        Application::Get().blockImGuiEvents(!m_isFocused || !m_isHovered);

        ImVec2 size  = ImGui::GetContentRegionAvail();
        if (size.x != m_framebuffer->getWidth() || size.y != m_framebuffer->getHeight())
        {
            m_framebuffer->resize(size.x, size.y);
            glViewport(0, 0, size.x, size.y);
            ViewportResizeEvent e(this, size.x, size.y);
            m_eventCallback(e);
        }

        notify();

        ImGui::Image((void*) m_framebuffer->getTextureId(), size, {0,1}, {1,0});

        ImGui::End();
        ImGui::PopStyleVar();
    }
}
