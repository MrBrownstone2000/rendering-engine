#ifndef __IMGUILAYER_HPP__
#define __IMGUILAYER_HPP__

#include "../events/mouseEvent.hpp"
#include "../events/keyEvent.hpp"
#include "../events/windowEvent.hpp"

#include <functional>

namespace engine
{
    class ImGuiManager
    {
        public:
            ImGuiManager();
            ~ImGuiManager();

            void init();

            void onEvent(Event& e);

            void beginFrame();
            void endFrame();

            void blockEvents(bool block);

            std::function<void(void*)> GetEventCallback();

        private:
            void makeDockSpace();

            static void EventCallback(void* nativeEvent);

        private:
            bool m_blockEvents;
    };
}

#endif
