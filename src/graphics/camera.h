#ifndef CAMERA_H
#define CAMERA_H

#include "glm/trigonometric.hpp"
namespace graphics {

    struct ViewportRect {
        uint32_t x;
        uint32_t y;
        uint32_t width;
        uint32_t height;
    };

    class Camera {
    public:
        Camera(const ViewportRect& rect);

        void Update(float timestep);

        const glm::mat4 GetViewProjection() const { return m_projectionMatrix * m_viewMatrix; };

        glm::vec3 GetPosition() const { return m_position; };
        void SetPosition(glm::vec3 newPosition) { m_position = newPosition; UpdateViewMatrix(); };
        glm::vec3 GetPitchYawRoll() const { return m_pitchYawRoll; };
        void SetPitchYawRoll(glm::vec3 newPitchYawRoll) { m_pitchYawRoll = newPitchYawRoll; UpdateViewMatrix(); };

    private:
        void UpdateProjectionMatrix();
        void UpdateViewMatrix();
        void UpdateOrbitCameraView();

    private:
        float m_fov = 70;
        float m_nearPlane = 0.1f;
        float m_farPlane = 1000.0f;
        ViewportRect m_viewport;
        glm::mat4 m_projectionMatrix = glm::mat4(1.0f);

        glm::vec3 m_position = glm::vec3(0);
        glm::vec3 m_pitchYawRoll = glm::vec3(0); // Free cam view

        glm::vec3 m_orbitalTarget = glm::vec3(0);
        glm::vec3 m_rhoPhiTheta = glm::vec3(10, 0, glm::radians(45.f)); // For spherical coords
        glm::mat4 m_viewMatrix = glm::mat4(1.0f);

    // For controls
    private:
        float m_lastMouseXpos = 0;
        float m_lastMouseYpos = 0;
    };

}

#endif /* CAMERA.H */
