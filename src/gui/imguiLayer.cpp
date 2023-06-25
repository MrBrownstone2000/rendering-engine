#include "events/eventDispatcher.hpp"
#include "pch.hpp"
#include "imguiLayer.hpp"
#include "../core/app.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl2.h"

#include <SDL.h>

namespace engine::gui
{
    ImGuiLayer::ImGuiLayer()
        : ILayer("ImGuiLayer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGuiStyle& style = ImGui::GetStyle();
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // ImGui_ImplSDL2_InitForOpenGL(app.GetWindow(), void *sdl_gl_context)

        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void ImGuiLayer::OnDetach()
    {
    }

    void ImGuiLayer::OnUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
        
        float time = SDL_GetTicks();
        io.DeltaTime = m_time > 0.f ? (time - m_time) : (1.f / 60.f);
        m_time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(events::Event& e)
    {
        events::EventDispatcher d(e); 
        d.Dispatch<events::MouseButtonPressedEvent>(M_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressed));
        d.Dispatch<events::MouseButtonReleasedEvent>(M_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleased));
        d.Dispatch<events::MouseMovedEvent>(M_BIND_EVENT_FN(ImGuiLayer::OnMouseMoved));
        d.Dispatch<events::MouseScrolledEvent>(M_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolled));
    }

    bool ImGuiLayer::OnMouseButtonPressed(events::MouseButtonPressedEvent& e)
    {
        int mouse_button = e.GetMouseButton();
        if (mouse_button == input::MouseButtonType::Unknown)
            return false;

        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseSourceEvent(ImGuiMouseSource_Mouse);
        io.AddMouseButtonEvent(mouse_button, true);
        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleased(events::MouseButtonReleasedEvent& e)
    {
        int mouse_button = e.GetMouseButton();
        if (mouse_button == input::MouseButtonType::Unknown)
            return false;

        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseSourceEvent(ImGuiMouseSource_Mouse);
        io.AddMouseButtonEvent(mouse_button, false);
        return false;
    }

    bool ImGuiLayer::OnMouseScrolled(events::MouseScrolledEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseSourceEvent(ImGuiMouseSource_Mouse);
        io.AddMouseWheelEvent(-e.getX(), e.getY());
        return false;
    }

    bool ImGuiLayer::OnMouseMoved(events::MouseMovedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImVec2 pos(e.getX(), e.getY());

        io.AddMouseSourceEvent(ImGuiMouseSource_Mouse);
        io.AddMousePosEvent(pos.x, pos.y);
        return false;
    }

    bool ImGuiLayer::OnText(events::TextEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharactersUTF8(e.GetText());
        return false;
    }

    bool ImGuiLayer::OnKeyPressed(events::KeyPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.AddKeyEvent(ImGuiMod_Ctrl, (e.GetKeyMods() & input::KeyModifier::Ctrl) != 0);
        io.AddKeyEvent(ImGuiMod_Shift, (e.GetKeyMods() & input::KeyModifier::Shift) != 0);
        io.AddKeyEvent(ImGuiMod_Alt, (e.GetKeyMods() & input::KeyModifier::Alt) != 0);
        io.AddKeyEvent(ImGuiMod_Super, (e.GetKeyMods() & input::KeyModifier::Super) != 0);

        return false;
    }

    bool ImGuiLayer::OnKeyReleased(events::KeyReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        io.AddKeyEvent(ImGuiMod_Ctrl, (e.GetKeyMods() & input::KeyModifier::Ctrl) != 0);
        io.AddKeyEvent(ImGuiMod_Shift, (e.GetKeyMods() & input::KeyModifier::Shift) != 0);
        io.AddKeyEvent(ImGuiMod_Alt, (e.GetKeyMods() & input::KeyModifier::Alt) != 0);
        io.AddKeyEvent(ImGuiMod_Super, (e.GetKeyMods() & input::KeyModifier::Super) != 0);

        return false;
    }
}
