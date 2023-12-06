#ifndef __CAMERACONTROLLER_HPP__
#define __CAMERACONTROLLER_HPP__

#include "camera.hpp"
#include "../events/event.hpp"
#include "../events/windowEvent.hpp"
#include "../events/mouseEvent.hpp"
#include "../events/viewportEvent.hpp"
#include "../events/keyEvent.hpp"
#include <memory>

namespace engine
{
    class PerspectiveCameraController
    {
        public:
            PerspectiveCameraController() = default;
            PerspectiveCameraController(std::shared_ptr<PerspectiveCamera> camera, 
                    float mouseSensitivity = 0.2f, float cameraSpeed = 0.1f);

            void update(float dt);
            void onEvent(Event& event);

            void setPitch(float pitch);
            void setYaw(float yaw);
            void setViewport(std::shared_ptr<ImGuiViewport> viewport);

            float& getYaw();
            float& getPitch();
            const std::shared_ptr<PerspectiveCamera> getCamera() const { return m_camera; }

        private:
            void changeOrientation(float offsetYaw, float offsetPitch);
            void updatePosition(Direction dir, float dt);
            void updateVectors();

            bool onMouseScroll(const MouseScrolledEvent& event);
            bool onViewportResize(const ViewportResizeEvent& event);
            bool onWindowResize(const WindowResizeEvent& event);
            bool onKeyPressed(const KeyPressedEvent& event);

        private:
            std::shared_ptr<PerspectiveCamera> m_camera;
            std::shared_ptr<ImGuiViewport> m_viewport;

            float m_yaw;
            float m_pitch;

            float m_mouseSensitivity;
            float m_cameraSpeed;
            bool m_captureMouse;
    };
}


#endif
