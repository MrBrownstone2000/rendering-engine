#include "pch.hpp"
#include "events/eventDispatcher.hpp"
#include "gui/imGuiManager.hpp"
#include "core/app.hpp"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

#include <SDL.h>
#include <GL/glew.h>

namespace engine
{
    ImGuiManager::ImGuiManager()
        : m_blockEvents(false), m_disableInputs(false)
    {
    }

    void ImGuiManager::init()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

        io.ConfigViewportsNoTaskBarIcon = true;
        // io.ConfigViewportsNoAutoMerge = true;

        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        style.WindowMenuButtonPosition = ImGuiDir_None;

        Application& app = Application::Get();
        SDL_Window* window = static_cast<SDL_Window*>(app.GetWindow().getNativeWindow());
        SDL_GLContext* gl_context = static_cast<SDL_GLContext*>(app.GetWindow().getContext()->getNativeContext());

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    ImGuiManager::~ImGuiManager()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    std::function<void(void*)> ImGuiManager::GetEventCallback()
    {
        return EventCallback;
    }

    void ImGuiManager::onEvent(Event& e)
    {
        if (!m_disableInputs && m_blockEvents)
        {
            ImGuiIO& io = ImGui::GetIO();
            e.m_handled |= e.isInCategory(EventCategory_Mouse) && io.WantCaptureMouse;
            e.m_handled |= e.isInCategory(EventCategory_Keyboard) && io.WantCaptureKeyboard;
        }
    }

    void ImGuiManager::blockEvents(bool block)
    {
        m_blockEvents = block;
    }

    void ImGuiManager::disableInputs(bool disable)
    {
        m_disableInputs = disable;
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags ^= ImGuiConfigFlags_NoMouse;
    }

    void ImGuiManager::EventCallback(void* nativeEvent)
    {
        ImGui_ImplSDL2_ProcessEvent((SDL_Event*) nativeEvent);
    }

    void ImGuiManager::beginFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        makeDockSpace();
    }

    void ImGuiManager::makeDockSpace()
    {
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        const ::ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | 
                        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::Begin("DockSpace Demo", nullptr, window_flags);
        {
            ImGui::PopStyleVar(3);

            // Submit the DockSpace
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("Options"))
                {
                    if (ImGui::MenuItem("Close"))
                        Application::Get().close();
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            ImGui::End();
        }
    }

    void ImGuiManager::endFrame()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().getWidth(), app.GetWindow().getHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
        SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }
}
