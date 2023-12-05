#include "pch.hpp"
#include "cameraController.hpp"
#include "input/input.hpp"
#include "events/eventDispatcher.hpp"

namespace engine
{
    PerspectiveCameraController::PerspectiveCameraController(std::shared_ptr<PerspectiveCamera> camera, float mouseSensitivity, float cameraSpeed)
        : m_camera(camera), m_yaw(0), m_pitch(0),
          m_mouseSensitivity(mouseSensitivity), m_cameraSpeed(cameraSpeed)
    {
        updateVectors();
        m_camera->recomputeViewProjection();
    }

    void PerspectiveCameraController::setPitch(float pitch)
    {
        m_pitch = pitch;
        updateVectors();
        m_camera->recomputeViewProjection();
    }

    void PerspectiveCameraController::setYaw(float yaw)
    {
        m_yaw = yaw;
        updateVectors();
        m_camera->recomputeViewProjection();
    }

    void PerspectiveCameraController::setViewport(std::shared_ptr<ImGuiViewport> viewport)
    {
        m_viewport = viewport;
    }

    void PerspectiveCameraController::changeOrientation(float offsetYaw, float offsetPitch)
    {
        m_yaw += offsetYaw * m_mouseSensitivity;
        m_pitch -= offsetPitch * m_mouseSensitivity;

        updateVectors();
    }

    void PerspectiveCameraController::updatePosition(Direction dir, float dt)
    {
        const glm::vec3& cameraPos = m_camera->getPosition();
        const glm::vec3& cameraDir = m_camera->getDirection();
        const glm::vec3& cameraRight = m_camera->getRight();
        const glm::vec3& cameraUp = m_camera->getUp();
        
        switch (dir)
        {
        case Direction::Front:
            m_camera->setPosition(cameraPos + dt * m_cameraSpeed * cameraDir);
            break;
        case Direction::Back:
            m_camera->setPosition(cameraPos - dt * m_cameraSpeed * cameraDir);
            break;
        case Direction::Left:
            m_camera->setPosition(cameraPos - dt * m_cameraSpeed * cameraRight);
            break;
        case Direction::Right:
            m_camera->setPosition(cameraPos + dt * m_cameraSpeed * cameraRight);
            break;
        case Direction::Up:
            m_camera->setPosition(cameraPos + dt * 0.7f * m_cameraSpeed * cameraUp);
            break;
        case Direction::Down:
            m_camera->setPosition(cameraPos - dt * 0.7f * m_cameraSpeed * cameraUp);
            break;

        default:
            break;
        }
    }

    void PerspectiveCameraController::updateVectors()
    {
        m_pitch = glm::clamp(m_pitch, -89.f, 89.f);
        m_yaw = glm::mod(m_yaw, 360.f);

        glm::vec3 dir;
        dir.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        dir.y = sin(glm::radians(m_pitch));
        dir.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

        m_camera->setDirection(glm::normalize(dir));
        m_camera->setRight(glm::normalize(glm::cross(m_camera->getDirection(), m_camera->getWorldUp())));
        m_camera->setUp(glm::normalize(glm::cross(m_camera->getRight(), m_camera->getDirection())));
    }

    void PerspectiveCameraController::update(float dt)
    {
        changeOrientation(input::GetMouseOffsetX(), input::GetMouseOffsetY());

        if (input::IsKeyPressed(KeyCode::Key_z))
            updatePosition(Direction::Front, dt);
        if (input::IsKeyPressed(KeyCode::Key_q))
            updatePosition(Direction::Left, dt);
        if (input::IsKeyPressed(KeyCode::Key_s))
            updatePosition(Direction::Back, dt);
        if (input::IsKeyPressed(KeyCode::Key_d))
            updatePosition(Direction::Right, dt);
        if (input::IsKeyPressed(KeyCode::Space))
            updatePosition(Direction::Up, dt);
        if (input::IsKeyPressed(KeyCode::LShift))
            updatePosition(Direction::Down, dt);
        
        m_camera->recomputeViewProjection();
    }

    float& PerspectiveCameraController::getYaw()
    {
        return m_yaw;
    }

    float& PerspectiveCameraController::getPitch()
    {
        return m_pitch;
    }

    bool PerspectiveCameraController::onMouseScroll(const MouseScrolledEvent& event)
    {
        m_camera->changeFOV(event.getY());
        m_camera->recomputeViewProjection();
        return false;
    }

    bool PerspectiveCameraController::onViewportResize(const ViewportResizeEvent& event)
    {
        if (event.getViewport() == m_viewport.get())
        {
            m_camera->setWindowSize(event.getWidth(), event.getHeight());
            m_camera->recomputeViewProjection();
        }
        return false;
    }

    bool PerspectiveCameraController::onWindowResize(const WindowResizeEvent& event)
    {
        m_camera->setWindowSize(event.getWidth(), event.getHeight());
        m_camera->recomputeViewProjection();
        return false;
    }
    
    void PerspectiveCameraController::onEvent(Event& event)
    {
        EventDispatcher d(event);
        // d.dispatch<WindowResizeEvent>(M_BIND_EVENT_FN(PerspectiveCameraController::onWindowResize));
        d.dispatch<MouseScrolledEvent>(M_BIND_EVENT_FN(PerspectiveCameraController::onMouseScroll));
        d.dispatch<ViewportResizeEvent>(M_BIND_EVENT_FN(PerspectiveCameraController::onViewportResize));
    }
}
