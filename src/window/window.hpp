#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <memory>
#include "../util/types.hpp"

namespace engine::window
{
    void Boot();

    class IWindow
    {
        public:
            IWindow() = default;
            virtual ~IWindow() = default;

            IWindow(const IWindow& rhs) = delete;
            IWindow& operator=(const IWindow& rhs) = delete;

            virtual bool OnUpdate() = 0;
            virtual void SwapBuffers() = 0;
    };

    std::unique_ptr<IWindow> Create(uint width, uint height);
}

#endif
