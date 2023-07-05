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

            virtual bool IsVSync() const = 0;
            virtual uint GetWidth() const = 0;
            virtual uint GetHeight() const = 0;
            virtual void* GetNativeWindow() = 0;
            virtual renderer::IContext* GetContext() = 0;

            virtual void OnUpdate() = 0;
            virtual void SwapBuffers() = 0;
            virtual void SetVSync(bool enabled) = 0;
            virtual void SetEventCallback(const EventCallback& cb) = 0;
            void SetImGuiCallback(std::function<void(void*)> cb) { m_imGuiEventCallback = cb; }

        protected:
            std::function<void(void*)> m_imGuiEventCallback;
    };
}

#endif
