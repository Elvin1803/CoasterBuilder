#include <pch.h>
#include "camera.h"

namespace scene {

    Camera::Camera(ViewportRect viewportRect)
        : m_viewportRect(viewportRect) {
        UpdateProjectionMatrix();
    }

    void Camera::UpdateProjectionMatrix() {
        float aspectRatio = (float)m_viewportRect.width / (float)m_viewportRect.height;
        m_projectionMatrix =
            glm::perspective(glm::radians(m_fov), aspectRatio, m_nearPlane, m_farPlane);
    }

    void Camera::UpdateViewMatrix() {
        auto orientation = glm::quat(glm::radians(m_pitchYawRoll) * glm::vec3(1, -1, -1));
        m_viewMatrix = glm::translate(glm::mat4(1.0f), m_position) * glm::toMat4(orientation);
        m_viewMatrix = glm::inverse(m_viewMatrix);
    }

}
