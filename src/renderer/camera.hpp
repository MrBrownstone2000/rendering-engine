#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <glm/glm.hpp>
#include "../util/types.hpp"
#include <SDL2/SDL.h>

namespace engine
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

    class Camera
    {
        public:
            Camera(uint32_t width, uint32_t height);
            virtual ~Camera() = default;

            glm::mat4 getView() const { return m_view; }
            glm::mat4 getProjection() const { return m_projection; }
            glm::mat4 getViewProjection() const { return m_viewProjection; }

            const glm::vec3& getPosition() const { return m_position; }
            const glm::vec3& getDirection() const { return m_direction; }
            const glm::vec3& getRight() const { return m_right; }
            const glm::vec3& getUp() const { return m_up; }
            const glm::vec3& getWorldUp() const { return m_worldUp; }

            void setWindowSize(unsigned int width, unsigned int height);
            void setPosition(const glm::vec3& position);
            void setDirection(const glm::vec3& direction);
            void setRight(const glm::vec3& right);
            void setUp(const glm::vec3& up);

            void recomputeViewProjection();

        private:
            virtual void recomputeProjection() = 0;
            void recomputeView();

        protected:
            glm::mat4 m_projection = glm::mat4(1);
            glm::mat4 m_view = glm::mat4(1);
            glm::mat4 m_viewProjection = glm::mat4(1);

            glm::vec3 m_position = glm::vec3(0);
            glm::vec3 m_direction = glm::vec3(0);

            const glm::vec3 m_worldUp;
            glm::vec3 m_up;
            glm::vec3 m_right;

            uint32_t m_windowWidth;
            uint32_t m_windowHeight;
    };

    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(uint32_t width = 1280, uint32_t height = 720);

        void setFOV(float fov);
        float getFOV() const;
        void changeFOV(float offsetFOV);

        void recomputeProjection() override;

    private:
        float m_fov;
    };
}

#endif // __CAMERA_HPP__
