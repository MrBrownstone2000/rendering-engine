#ifndef __SDLWINDOW_HPP__
#define __SDLWINDOW_HPP__

#include "window.hpp"
#include "../gfx/context.hpp"

#include <memory>
#include <string>
#include <functional>

class SDL_Window;

namespace engine
{
    class SDLWindow : public Window
    {
        public:
            SDLWindow(const window::WindowParams& p);
            ~SDLWindow();

            bool isVSync() const override;
            uint getWidth() const override;
            uint getHeight() const override;
            void* getNativeWindow() override;
            IRenderingContext* getContext() override;

            void onUpdate() override;
            void swapBuffers() override;
            void setVSync(bool enabled) override;
            void setCaptureMouse(bool enabled) override;

            static void Boot();

        private:
            void HandleEvents();

        private:
            SDL_Window* m_window;
            std::unique_ptr<IRenderingContext> m_context;
            uint m_width, m_height;
            bool m_vsync, m_captureMouse;

            static inline bool m_isGlewInit = false;
    };
}

#endif
