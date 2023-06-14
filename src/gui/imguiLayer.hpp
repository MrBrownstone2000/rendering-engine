#ifndef __IMGUILAYER_HPP__
#define __IMGUILAYER_HPP__

#include "../core/layer.hpp"

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
            void OnEvent(events::Event&);

        private:
            float m_time = 0.f;
    };
}

#endif
