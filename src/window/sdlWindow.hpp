#ifndef __SDLWINDOW_HPP__
#define __SDLWINDOW_HPP__

#include "window.hpp"
#include "../renderer/context.hpp"

#include <memory>
#include <string>
#include <functional>

class SDL_Window;

namespace engine::window
{
    class SDLWindow : public IWindow
    {
        public:
            SDLWindow(const IocParams& p);
            ~SDLWindow();

            bool isVSync() const override;
            uint getWidth() const override;
            uint getHeight() const override;
            void* getNativeWindow() override;
            renderer::IContext* getContext() override;

            void onUpdate() override;
            void swapBuffers() override;
            void setVSync(bool enabled) override;
            void setEventCallback(const EventCallback& cb) override;

            static void Boot();

        private:
            void HandleEvents();

        private:
            SDL_Window* m_window;
            std::unique_ptr<renderer::IContext> m_context;
            uint m_width, m_height;
            bool m_vsync;

            EventCallback m_eventCallback;

            static inline bool m_isGlewInit = false;
    };
}

#endif
