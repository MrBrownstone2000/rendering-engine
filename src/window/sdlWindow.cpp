#include "pch.hpp"
#include "sdlWindow.hpp"

#include "SDL.h"
#include "GL/glew.h"
#include <memory>

namespace engine::window
{
    class WindowImpl
    {
        public:
            SDL_Window* window;
            SDL_GLContext glContext;
            static inline bool isGlewInit = false;
    };

    void Boot()
    {
        Check(SDL_Init(SDL_INIT_VIDEO) >= 0)
            .msg("Error: Could not initalize SDL...");

        const char* glsl_version = "#version 460";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    }

    std::unique_ptr<Window> Create(uint width, uint height)
    {
        return std::make_unique<SDLWindow>(width, height);
    }

    SDLWindow::SDLWindow(uint width, uint height)
        : m_pImpl(std::make_unique<WindowImpl>())
    {
        engineLog.info("Creating Window");

        m_pImpl->window = SDL_CreateWindow(
                "GUI App",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                width, height,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
                SDL_WINDOW_RESIZABLE    //  | SDL_WINDOW_FULLSCREEN
                );

        Check(m_pImpl->window).msg("Error: could not create window...");

        m_pImpl->glContext = SDL_GL_CreateContext(m_pImpl->window);
        Check(m_pImpl->glContext).msg("Error: [GL] failed to get GL context from window");

        if (!WindowImpl::isGlewInit)
        {
            GLenum err = glewInit();
            if (err != GLEW_OK)
            {
                std::stringstream oss;
                oss << "GLEW Error: " << glewGetErrorString(err) << "\n";
                Check(false).msg(oss.str());
            }
            WindowImpl::isGlewInit = true;
        }
    }

    SDLWindow::~SDLWindow()
    {
        SDL_GL_DeleteContext(m_pImpl->glContext);
        SDL_DestroyWindow(m_pImpl->window);
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
                    event.window.windowID == SDL_GetWindowID(m_pImpl->window)
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
        SDL_GL_SwapWindow(m_pImpl->window);
    }
}
