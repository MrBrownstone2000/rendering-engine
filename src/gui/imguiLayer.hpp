#ifndef __IMGUILAYER_HPP__
#define __IMGUILAYER_HPP__

#include "../core/layer.hpp"
#include "../events/mouseEvent.hpp"
#include "../events/keyEvent.hpp"
#include "../events/windowEvent.hpp"

namespace engine::gui
{
    class ImGuiLayer : public ILayer
    {
        public:
            ImGuiLayer();
            ~ImGuiLayer();

            void OnAttach();
            void OnDetach();
            void OnUpdate();
            void OnEvent(events::Event& e);

        private:
            bool OnMouseButtonPressed(events::MouseButtonPressedEvent& e);
            bool OnMouseButtonReleased(events::MouseButtonReleasedEvent& e);
            bool OnMouseScrolled(events::MouseScrolledEvent& e);
            bool OnMouseMoved(events::MouseMovedEvent& e);
            bool OnText(events::TextEvent& e);
            bool OnKeyPressed(events::KeyPressedEvent& e);
            bool OnKeyReleased(events::KeyReleasedEvent& e);

        private:
            float m_time = 0.f;
    };
}

#endif
