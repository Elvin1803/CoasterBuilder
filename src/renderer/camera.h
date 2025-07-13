#ifndef CAMERA_H
#define CAMERA_H

namespace renderer {

    struct ViewportRect {
        uint32_t x;
        uint32_t y;
        uint32_t width;
        uint32_t height;
    };

    class Camera {
    public:
        Camera(ViewportRect viewportRect);
        ~Camera() = default;

        const glm::mat4 GetViewProjection() const { return m_projectionMatrix * m_viewMatrix; };

#ifdef DEBUG
        glm::vec3 GetPosition() const { return m_position; };
        void SetPosition(glm::vec3 newPosition) { m_position = newPosition; UpdateViewMatrix(); };
        glm::vec3 GetPitchYawRoll() const { return m_pitchYawRoll; };
        void SetPitchYawRoll(glm::vec3 newPitchYawRoll) { m_pitchYawRoll = newPitchYawRoll; UpdateViewMatrix(); };
#endif /* DEBUG */

    private:
        void UpdateProjectionMatrix();
        void UpdateViewMatrix();

    private:
        float m_fov = 70;
        float m_nearPlane = 0.1f;
        float m_farPlane = 1000.0f;
        ViewportRect m_viewportRect;
        glm::mat4 m_projectionMatrix = glm::mat4(1.0f);

        glm::vec3 m_position = glm::vec3(0);
        glm::vec3 m_pitchYawRoll  = glm::vec3(0);
        glm::mat4 m_viewMatrix = glm::mat4(1.0f);
    };

}

#endif /* CAMERA.H */
