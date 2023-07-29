#ifndef __IMGUILAYER_HPP__
#define __IMGUILAYER_HPP__

#include "../core/layer.hpp"
#include "../events/mouseEvent.hpp"
#include "../events/keyEvent.hpp"
#include "../events/windowEvent.hpp"

#include <functional>

namespace engine
{
    class ImGuiLayer : public ILayer
    {
        public:
            ImGuiLayer();
            ~ImGuiLayer();

            void onAttach() override;
            void onDetach() override;
            void onImGuiRender() override;

            void beginFrame();
            void endFrame();

            std::function<void(void*)> GetEventCallback();

        private:
            static void EventCallback(void* nativeEvent);
    };
}

#endif
