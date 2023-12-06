#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <functional>
#include <memory>
#include <string>
#include "../util/types.hpp"
#include "../events/event.hpp"
#include "../gfx/context.hpp"

namespace engine
{
    class Window;

    namespace window
    {
        struct WindowParams 
        {
            uint width;
            uint height;
            std::string title;
        };

        void Boot();
        std::shared_ptr<Window> Create(const WindowParams& params);
    }


    class Window
    {
        public:
            using EventCallback = std::function<void(Event&)>;
            virtual ~Window() = default;

            virtual bool isVSync() const = 0;
            virtual uint getWidth() const = 0;
            virtual uint getHeight() const = 0;
            virtual void* getNativeWindow() = 0;
            virtual IRenderingContext* getContext() = 0;

            virtual void onUpdate() = 0;
            virtual void swapBuffers() = 0;
            virtual void setVSync(bool enabled) = 0;
            virtual void setCaptureMouse(bool enabled) = 0;
            void setEventCallback(const EventCallback& cb);
            void setImGuiCallback(std::function<void(void*)> cb);

        protected:
            std::function<void(void*)> m_imGuiEventCallback;
            EventCallback m_eventCallback;

    };
}

#endif
