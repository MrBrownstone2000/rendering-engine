#include "pch.hpp"
#include "sdlWindow.hpp"

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

        const char* glsl_version = "#version 460";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    }

    std::unique_ptr<IWindow> Create(uint width, uint height)
    {
        return std::make_unique<SDLWindow>(width, height);
    }

    SDLWindow::SDLWindow(uint width, uint height)
    {
        engineLog.info("Creating Window");

        m_window = SDL_CreateWindow(
                "GUI App",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                width, height,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
                SDL_WINDOW_RESIZABLE    //  | SDL_WINDOW_FULLSCREEN
                );

        Check(m_window).msg("Error: could not create window...");

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

    SDLWindow::~SDLWindow()
    {
        SDL_DestroyWindow(m_window);
    }

    bool SDLWindow::OnUpdate()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // ImGui_ImplSDL2_ProcessEvent(&event);
            // "close requested" event: we close the window
            if (event.type == SDL_QUIT)
                return false;
            else if (event.type == SDL_WINDOWEVENT &&
                    event.window.event == SDL_WINDOWEVENT_CLOSE &&
                    event.window.windowID == SDL_GetWindowID(m_window)
                    )
                return false;
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    return false;
            }
            // Change the viewport when the window is resized
            // else if (event.type == SDL_WINDOWEVENT &&
            //         event.window.event == SDL_WINDOWEVENT_RESIZED)
            // {
            // }
            // if (event.type == SDL_MOUSEWHEEL)
            // {
            // }
        }
        return true;
    }
    
    void SDLWindow::SwapBuffers()
    {
        m_context->SwapBuffers();
    }
}
