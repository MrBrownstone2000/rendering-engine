#include "pch.hpp"
#include "camera.hpp"

#include "input/input.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace engine
{
    Camera::Camera(uint32_t width, uint32_t height)
        : m_worldUp(0, 1, 0), m_windowWidth(width), m_windowHeight(height)
    {
    }

    void Camera::recomputeView()
    {
        m_view = glm::lookAt(m_position, m_position + m_direction, m_up);
    }

    void Camera::recomputeViewProjection()
    {
        recomputeView();
        recomputeProjection();
        m_viewProjection = m_projection * m_view;
    }

    void Camera::setWindowSize(unsigned int width, unsigned int height)
    {
        m_windowWidth = width;
        m_windowHeight = height;
    }

    void Camera::setPosition(const glm::vec3& position)
    {
        m_position = position;
    }

    void Camera::setDirection(const glm::vec3& direction)
    {
        m_direction = direction;
    }

    void Camera::setRight(const glm::vec3& right)
    {
        m_right = right;
    }

    void Camera::setUp(const glm::vec3& up)
    {
        m_up = up;
    }

    PerspectiveCamera::PerspectiveCamera(uint32_t width, uint32_t height)
        : Camera(width, height), m_fov(70)
    {
    }


    void PerspectiveCamera::setFOV(float fov)
    {
        m_fov = glm::clamp(fov, 1.f, 90.f);
    }

    float PerspectiveCamera::getFOV() const
    {
        return m_fov;
    }

    void PerspectiveCamera::changeFOV(float offsetFOV)
    {
        m_fov = glm::clamp(m_fov + offsetFOV, 1.f, 90.f);
    }

    void PerspectiveCamera::recomputeProjection()
    {
        m_projection = glm::perspective(glm::radians(m_fov), float(m_windowWidth) / float(m_windowHeight), 0.1f, 200.f);
    }
}

