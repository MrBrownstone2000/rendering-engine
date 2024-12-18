#include "pch.hpp"
#include "window/sdlWindow.hpp"

#include "events/keyEvent.hpp"
#include "events/mouseEvent.hpp"
#include "events/windowEvent.hpp"
#include "gfx/openGLContext.hpp"
#include "input/input.hpp"
#include "input/sdlKeyCodes.hpp"
#include "renderer/renderer.hpp"
#include "core/app.hpp"

#include <SDL.h>
#include <GL/glew.h>
#include <memory>


namespace engine
{
    void SDLWindow::Boot()
    {
        Check(SDL_Init(SDL_INIT_VIDEO) >= 0)
            .msg("Error: Could not initalize SDL...");

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    }

    SDLWindow::SDLWindow(const window::WindowParams& p)
    {
        engineLog.info("Creating Window");

        m_width = p.width;
        m_height = p.height;
        m_vsync = true;
        m_captureMouse = false;

        m_window = SDL_CreateWindow(
                p.title.c_str(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                m_width, m_height,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
                SDL_WINDOW_RESIZABLE    //  | SDL_WINDOW_FULLSCREEN
                );

        Check(m_window).msg("Error: could not create window...");

        m_context = std::make_unique<OpenGLContext>(m_window);

        // SDL_SetRelativeMouseMode(SDL_TRUE);
        SDL_GL_SetSwapInterval(1);

        if (!m_isGlewInit)
        {
            GLenum err = glewInit();
            if (err != GLEW_OK)
            {
                std::stringstream oss;
                oss << "GLEW Error: " << glewGetErrorString(err) << "\n";
                engineLog.fatal(oss.str());
            }
            m_isGlewInit = true;
            renderer::Boot();
        }
    }
    uint SDLWindow::getWidth() const
    {
        return m_width;
    }

    uint SDLWindow::getHeight() const
    {
        return m_height;
    }

    void* SDLWindow::getNativeWindow() 
    {
        return m_window;
    }

    IRenderingContext* SDLWindow::getContext()
    {
        return m_context.get();
    }

    void SDLWindow::setVSync(bool enabled)
    {
        m_vsync = enabled;
        SDL_GL_SetSwapInterval(enabled);
    }

    void SDLWindow::setCaptureMouse(bool enabled)
    {
        m_captureMouse = enabled;
        SDL_SetRelativeMouseMode(enabled ? SDL_TRUE : SDL_FALSE);
        Application::Get().GetImGuiManager().disableInputs(enabled);
    }

    bool SDLWindow::isVSync() const
    {
        return m_vsync;
    }

    SDLWindow::~SDLWindow()
    {
        SDL_DestroyWindow(m_window);
    }

    void SDLWindow::HandleEvents()
    {
        Check(m_imGuiEventCallback);

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (!m_captureMouse)
                m_imGuiEventCallback(&event);
            // ========== Window Events ==========
            if (event.type == SDL_QUIT)
            {
                WindowCloseEvent e;
                m_eventCallback(e);
            }
            else if (event.type == SDL_WINDOWEVENT && event.window.windowID == SDL_GetWindowID(m_window))
            {
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                    {
                        WindowCloseEvent e;
                        m_eventCallback(e);
                        break;
                    }
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                    {
                        WindowFocusEvent e;
                        m_eventCallback(e);
                        break;
                    }
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                    {
                        WindowLostFocusEvent e;
                        m_eventCallback(e);
                        break;
                    }
                    case SDL_WINDOWEVENT_RESIZED:
                    {
                        m_width = event.window.data1;
                        m_height = event.window.data2;

                        WindowResizeEvent e(m_width, m_height);
                        m_eventCallback(e);
                        break;
                    }
                    case SDL_WINDOWEVENT_MOVED:
                    {
                        WindowMovedEvent e(event.window.data1, event.window.data2);
                        m_eventCallback(e);
                        break;
                    }
                }
            }
            // ========== Mouse Events ==========
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                MouseButtonType b = GetMouseButtonType(event.button.button);
                if (b != MouseButtonType::Unknown)
                {
                    MouseButtonPressedEvent e(b);
                    m_eventCallback(e);
                }
            }
            if (event.type == SDL_MOUSEBUTTONUP)
            {
                MouseButtonType b = GetMouseButtonType(event.button.button);
                if (b != MouseButtonType::Unknown)
                {
                    MouseButtonReleasedEvent e(b);
                    m_eventCallback(e);
                }
            }
            if (event.type == SDL_MOUSEWHEEL)
            {
                MouseScrolledEvent e(event.wheel.preciseX, event.wheel.preciseY);
                m_eventCallback(e);
            }
            if (event.type == SDL_MOUSEMOTION)
            {
                MouseMovedEvent e(event.motion.x, event.motion.y,
                        event.motion.xrel, event.motion.yrel);
                m_eventCallback(e);
            }
            // ========== Keyboard Events ==========
            if (event.type == SDL_KEYDOWN)
            {
                KeyCode k = GetKeyCode(event.key.keysym.sym);
                if (k != KeyCode::Unknown)
                {
                    u8 mods = 0;
                    if (event.key.keysym.mod & KMOD_SHIFT)
                        mods |= KeyModifier::Shift;
                    if (event.key.keysym.mod & KMOD_ALT)
                        mods |= KeyModifier::Alt;
                    if (event.key.keysym.mod & KMOD_CTRL)
                        mods |= KeyModifier::Ctrl;
                    if (event.key.keysym.mod & KMOD_GUI)
                        mods |= KeyModifier::Super;
                    KeyPressedEvent e(k, mods, event.key.repeat);
                    m_eventCallback(e);
                }
            }
            if (event.type == SDL_KEYUP)
            {
                KeyCode k = GetKeyCode(event.key.keysym.sym);
                if (k != KeyCode::Unknown)
                {
                    u8 mods = 0;
                    if (event.key.keysym.mod & KMOD_SHIFT)
                        mods |= KeyModifier::Shift;
                    if (event.key.keysym.mod & KMOD_ALT)
                        mods |= KeyModifier::Alt;
                    if (event.key.keysym.mod & KMOD_CTRL)
                        mods |= KeyModifier::Ctrl;
                    if (event.key.keysym.mod & KMOD_GUI)
                        mods |= KeyModifier::Super;
                    KeyReleasedEvent e(k, mods);
                    m_eventCallback(e);
                }
            }
            if (event.type == SDL_TEXTINPUT)
            {
                TextEvent e(event.text.text);
                m_eventCallback(e);
            }
        }
        int x, y;
        SDL_GetRelativeMouseState(&x, &y);
        input::SetMouseOffset(x, y);
    }

    void SDLWindow::onUpdate()
    {
        HandleEvents();
    }

    void SDLWindow::swapBuffers()
    {
        m_context->swapBuffers();
    }
}
