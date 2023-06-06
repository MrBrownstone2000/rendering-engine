#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <functional>
#include <memory>
#include <string>
#include "../util/types.hpp"
#include "../events/event.hpp"

namespace engine::window
{
    void Boot();

    class IWindow
    {
        public:
            using EventCallback = std::function<void(events::Event&)>;
            virtual ~IWindow() = default;

            virtual uint GetWidth() const = 0;
            virtual uint GetHeight() const = 0;
            virtual bool IsVSync() const = 0;

            virtual void OnUpdate() = 0;
            virtual void SwapBuffers() = 0;
            virtual void SetVSync(bool enabled) = 0;
            virtual void SetEventCallback(const EventCallback& cb) = 0;
    };

    std::unique_ptr<IWindow> Create(uint width, uint height, std::string title);
}

#endif
