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

    enum class CameraType { Orbit, Free };

    class Camera {
    public:
        Camera(const ViewportRect& rect);

        void Update(float timestep);

        void SetViewportRect(const ViewportRect& v) { m_viewport = v; };
        const glm::mat4 GetViewProjection() const { return m_projectionMatrix * m_viewMatrix; };

        glm::vec3 GetPosition() const { return m_position; };

    private:
        void UpdateProjectionMatrix();
        void UpdateOrbitCameraView();
        void UpdateFreeCameraView();

        void HandleOrbitControls(float timestep);
        void HandleFreeControls(float timestep);

    private:
        float m_fov = 70;
        float m_nearPlane = 0.1f;
        float m_farPlane = 1000.0f;
        ViewportRect m_viewport;
        glm::mat4 m_projectionMatrix = glm::mat4(1.0f);

        // Free cam
        glm::vec3 m_position = glm::vec3(0);
        glm::vec3 m_pitchYawRoll = glm::vec3(0); // Free cam view

        // Orbital cam
        glm::vec3 m_orbitalTarget = glm::vec3(0);
        glm::vec3 m_rhoPhiTheta = glm::vec3(10, 0, glm::radians(45.f)); // For spherical coords

        glm::mat4 m_viewMatrix = glm::mat4(1.0f);

        CameraType m_cameraType = CameraType::Orbit;

    // For controls
    private:
        float m_lastMouseXpos = 0;
        float m_lastMouseYpos = 0;
    };

}

#endif /* CAMERA.H */
