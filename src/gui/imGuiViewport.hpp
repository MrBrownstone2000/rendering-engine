#ifndef __IMGUIVIEWPORT_HPP__
#define __IMGUIVIEWPORT_HPP__

#include "../events/event.hpp"
#include "../gfx/framebuffer.hpp"
#include "../util/observer.hpp"

#include <memory>
#include <functional>

namespace engine
{
    class ImGuiViewport : public util::Subject
    {
        public:
            using EventCallback = std::function<void(Event&)>;

            ImGuiViewport() = default;
            ImGuiViewport(std::shared_ptr<Framebuffer> framebuffer);
            void setEventCallback(const EventCallback& cb);

            const std::shared_ptr<Framebuffer> getFramebuffer() const;
            bool isFocused() const;
            bool isHovered() const;

            void onImGuiRender();

        private:
            std::shared_ptr<engine::Framebuffer> m_framebuffer;
            EventCallback m_eventCallback;
            bool m_isFocused;
            bool m_isHovered;
    };
}

#endif
