#include "pch.hpp"
#include "sdlWindow.hpp"
#include "../events/windowEvent.hpp"

#include "SDL.h"
#include "GL/glew.h"
#include <memory>

#include "../renderer/openGLContext.hpp"

namespace engine::window
{
    void Boot()
    {
        Check(SDL_Init(SDL_INIT_VIDEO) >= 0)
            .msg("Error: Could not initalize SDL...");

        // const char* glsl_version = "#version 460";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    }

    std::unique_ptr<IWindow> Create(uint width, uint height, std::string title)
    {
        return std::make_unique<SDLWindow>(width, height, title);
    }

    SDLWindow::SDLWindow(uint width, uint height, std::string title)
    {
        engineLog.info("Creating Window");

        m_window = SDL_CreateWindow(
                title.c_str(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                width, height,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
                SDL_WINDOW_RESIZABLE    //  | SDL_WINDOW_FULLSCREEN
                );

        Check(m_window).msg("Error: could not create window...");

        SDL_GL_SetSwapInterval(1);
        m_width = width;
        m_height = height;
        m_vsync = true;

        m_context = std::make_unique<renderer::OpenGLContext>(m_window);

        if (!m_isGlewInit)
        {
            GLenum err = glewInit();
            if (err != GLEW_OK)
            {
                std::stringstream oss;
                oss << "GLEW Error: " << glewGetErrorString(err) << "\n";
                Check(false).msg(oss.str());
            }
            m_isGlewInit = true;
        }
    }
    uint SDLWindow::GetWidth() const
    {
        return m_width;
    }

    uint SDLWindow::GetHeight() const
    {
        return m_height;
    }

    void SDLWindow::SetVSync(bool enabled)
    {
        m_vsync = enabled;
        SDL_GL_SetSwapInterval(enabled);
    }

    bool SDLWindow::IsVSync() const
    {
        return m_vsync;
    }

    SDLWindow::~SDLWindow()
    {
        SDL_DestroyWindow(m_window);
    }

    void SDLWindow::SetEventCallback(const EventCallback& cb)
    {
        m_eventCallback = cb;
    }

    void SDLWindow::HandleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // ImGui_ImplSDL2_ProcessEvent(&event);
            // "close requested" event: we close the window
            if (event.type == SDL_QUIT)
            {
                events::WindowCloseEvent e;
                m_eventCallback(e);
            }
            else if (event.type == SDL_WINDOWEVENT &&
                    event.window.event == SDL_WINDOWEVENT_CLOSE &&
                    event.window.windowID == SDL_GetWindowID(m_window)
                    )
            {
                events::WindowCloseEvent e;
                m_eventCallback(e);
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    events::WindowCloseEvent e;
                    m_eventCallback(e);
                }
            }
            // Change the viewport when the window is resized
            else if (event.type == SDL_WINDOWEVENT &&
                    event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                m_width = event.window.data1;
                m_height = event.window.data2;

                events::WindowResizeEvent e(m_width, m_height);
                m_eventCallback(e);
            }
            // if (event.type == SDL_MOUSEWHEEL)
            // {
            // }
        }
    }

    void SDLWindow::OnUpdate()
    {
        HandleEvents();
    }
    
    void SDLWindow::SwapBuffers()
    {
        m_context->SwapBuffers();
    }
}
