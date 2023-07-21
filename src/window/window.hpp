#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <functional>
#include <memory>
#include <string>
#include "../util/types.hpp"
#include "../events/event.hpp"
#include "../renderer/context.hpp"

namespace engine::window
{
    void Boot();

    class IWindow
    {
        public:
            struct IocParams {
                uint width;
                uint height;
                std::string title;
            };

            using EventCallback = std::function<void(events::Event&)>;
            virtual ~IWindow() = default;

            virtual bool isVSync() const = 0;
            virtual uint getWidth() const = 0;
            virtual uint getHeight() const = 0;
            virtual void* getNativeWindow() = 0;
            virtual renderer::IContext* getContext() = 0;

            virtual void onUpdate() = 0;
            virtual void swapBuffers() = 0;
            virtual void setVSync(bool enabled) = 0;
            virtual void setEventCallback(const EventCallback& cb) = 0;
            void setImGuiCallback(std::function<void(void*)> cb) { m_imGuiEventCallback = cb; }

        protected:
            std::function<void(void*)> m_imGuiEventCallback;
    };
}

#endif
