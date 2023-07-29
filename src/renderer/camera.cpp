#include "pch.hpp"
#include "camera.hpp"

#include "input/input.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace engine
{
    Camera::Camera(unsigned int width, unsigned int height, float mouseSensitivity, float cameraSpeed)
        : m_mouseSensitivity(mouseSensitivity),
          m_cameraSpeed(cameraSpeed),
          m_windowWidth(width),
          m_windowHeight(height)
    {
        m_cameraPos = glm::vec3(0.f, 0.f, 3.f);
        m_worldUp = glm::vec3(0.f, 1.f, 0.f);

        m_fov = 45.f;
        m_yaw = 0.f;
        m_pitch = 0;

        updateVectors();
    }

    void Camera::setFOV(float fov)
    {
        m_fov = fov;
        if (m_fov < 1.f)
            m_fov = 1.f;
        else if (m_fov > 90.f)
            m_fov = 90.f;
    }

    void Camera::changeOrientation(float offsetYaw, float offsetPitch)
    {
        m_yaw += offsetYaw * m_mouseSensitivity;
        m_pitch -= offsetPitch * m_mouseSensitivity;

        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;

        updateVectors();
    }

    void Camera::updatePosition(Direction dir, float dt)
    {
        switch (dir)
        {
        case Direction::Front:
            m_cameraPos += dt * m_cameraSpeed * m_cameraDirection;
            break;
        case Direction::Back:
            m_cameraPos -= dt * m_cameraSpeed * m_cameraDirection;
            break;
        case Direction::Left:
            m_cameraPos -= dt * m_cameraSpeed * m_right;
            break;
        case Direction::Right:
            m_cameraPos += dt * m_cameraSpeed * m_right;
            break;
        case Direction::Up:
            m_cameraPos += dt * 0.7f * m_cameraSpeed * m_up;
            break;
        case Direction::Down:
            m_cameraPos -= dt * 0.7f * m_cameraSpeed * m_up;
            break;

        default:
            break;
        }
        updateVectors();
    }

    void Camera::updateVectors()
    {
        glm::vec3 dir;
        dir.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        dir.y = sin(glm::radians(m_pitch));
        dir.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_cameraDirection = glm::normalize(dir);

        m_right = glm::normalize(glm::cross(m_cameraDirection, m_worldUp));
        m_up = glm::normalize(glm::cross(m_right, m_cameraDirection));
    }

    glm::mat4 Camera::view() const
    {
        return lookAt(m_cameraPos, m_cameraPos + m_cameraDirection, m_up);
    }

    glm::mat4 Camera::projection() const
    {
        return glm::perspective(glm::radians(m_fov), float(m_windowWidth) / float(m_windowHeight), 0.1f, 200.f);
    }

    glm::vec3 Camera::position() const
    {
        return m_cameraPos;
    }

    glm::vec3 Camera::direction() const
    {
        return m_cameraDirection;
    }

    glm::mat4 Camera::lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp) const
    {
        glm::vec3 zAxis = glm::normalize(position - target);
        glm::vec3 xAxis = glm::normalize(glm::cross(glm::normalize(worldUp), zAxis));
        glm::vec3 yAxis = glm::cross(zAxis, xAxis);

        glm::mat4 mat(1.f);

        mat[0][0] = xAxis.x;
        mat[1][0] = xAxis.y;
        mat[2][0] = xAxis.z;
        mat[0][1] = yAxis.x;
        mat[1][1] = yAxis.y;
        mat[2][1] = yAxis.z;
        mat[0][2] = zAxis.x;
        mat[1][2] = zAxis.y;
        mat[2][2] = zAxis.z;

        mat[3][0] = -glm::dot(xAxis, position);
        mat[3][1] = -glm::dot(yAxis, position);
        mat[3][2] = -glm::dot(zAxis, position);

        return mat;
    }

    void Camera::update(float dt)
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
    }

    float Camera::getFOV() const
    {
        return m_fov;
    }

    void Camera::setWindowSize(unsigned int width, unsigned int height)
    {
        m_windowWidth = width;
        m_windowHeight = height;
    }

    void Camera::setPosition(const glm::vec3& position)
    {
        m_cameraPos = position;
    }

    float& Camera::getYaw()
    {
        return m_yaw;
    }

    float& Camera::getPitch()
    {
        return m_pitch;
    }
}

