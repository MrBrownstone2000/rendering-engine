#ifndef __IMGUILAYER_HPP__
#define __IMGUILAYER_HPP__

#include "../core/layer.hpp"
#include "../events/mouseEvent.hpp"
#include "../events/keyEvent.hpp"
#include "../events/windowEvent.hpp"

#include <functional>

namespace engine::gui
{
    class ImGuiLayer : public ILayer
    {
        public:
            ImGuiLayer();
            ~ImGuiLayer();

            void OnAttach() override;
            void OnDetach() override;
            void OnImGuiRender() override;

            void Begin();
            void End();

            std::function<void(void*)> GetEventCallback();

        private:
            static void EventCallback(void* nativeEvent);

            float m_time = 0.f;
    };
}

#endif
