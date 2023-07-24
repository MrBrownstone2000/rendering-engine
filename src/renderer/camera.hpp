#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

namespace engine::renderer
{
    enum class Direction
    {
        Front,
        Back,
        Left,
        Right,
        Up,
        Down
    };

    // Perspective camera
    class Camera
    {
    public:
        Camera(unsigned int width = 800, unsigned int height = 600, float mouseSensitivity = 0.2f, float cameraSpeed = 0.01f);

        void update(float dt);

        void setWindowSize(unsigned int width, unsigned int height);
        void setFOV(float fov);
        void setPosition(const glm::vec3& pos);

        float getFOV() const;
        float& getYaw();
        float& getPitch();

        glm::mat4 view() const;
        glm::mat4 projection() const;
        glm::vec3 position() const;
        glm::vec3 direction() const;

    private:
        void changeOrientation(float offsetYaw, float offsetPitch);
        void updatePosition(Direction dir, float dt);

        void updateVectors();
        glm::mat4 lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp) const;

    private:
        glm::vec3 m_cameraPos;
        glm::vec3 m_cameraDirection;
        glm::vec3 m_worldUp;
        glm::vec3 m_up;
        glm::vec3 m_right;

        float m_fov;
        float m_yaw;
        float m_pitch;

        float m_mouseSensitivity;
        float m_cameraSpeed;

        unsigned int m_windowWidth;
        unsigned int m_windowHeight;
    };
}

#endif // __CAMERA_HPP__
