#ifndef __SDLWINDOW_HPP__
#define __SDLWINDOW_HPP__

#include "events/mouseEvent.hpp"
#include "window.hpp"
#include "../renderer/context.hpp"
#include <SDL.h>
#include <memory>
#include <string>

namespace engine::window
{
    class WindowImpl;
    class SDLWindow : public IWindow
    {
        public:
            SDLWindow(uint width, uint height, std::string title);
            ~SDLWindow();

            virtual bool IsVSync() const override;
            virtual uint GetWidth() const override;
            virtual uint GetHeight() const override;

            void OnUpdate() override;
            void SwapBuffers() override;
            virtual void SetEventCallback(const EventCallback& cb) override;
            virtual void SetVSync(bool enabled) override;

        private:
            void HandleEvents();
            events::MouseButtonType GetMouseButtonType(u8 sdlButton) const;

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
