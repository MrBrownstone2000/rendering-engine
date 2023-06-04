#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <memory>
#include "../util/types.hpp"

namespace engine::window
{
    void Boot();

    class Window
    {
        public:
            Window() = default;
            virtual ~Window() = default;

            Window(const Window& rhs) = delete;
            Window& operator=(const Window& rhs) = delete;

            virtual bool OnUpdate() = 0;
            virtual void SwapBuffers() = 0;
    };

    std::unique_ptr<Window> Create(uint width, uint height);
}

#endif
