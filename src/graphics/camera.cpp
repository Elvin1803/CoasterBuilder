#include <pch.h>
#include "camera.h"

#include "utils/logger.h"
#include "input/input.h"

namespace graphics {

    Camera::Camera(const ViewportRect& rect)
        : m_viewport(rect) {
        UpdateProjectionMatrix();
    }

    void Camera::Update(float timestep) {
        (void)timestep;
        if (Input::IsActionPressed(InputAction::MOVE_FORWARD)) {
            LOG_TRACE("move fwd");
        }
    }

    void Camera::UpdateProjectionMatrix() {
        float aspectRatio = (float)m_viewport.width / (float)m_viewport.height;

        m_projectionMatrix =
            glm::perspective(glm::radians(m_fov), aspectRatio, m_nearPlane, m_farPlane);
    }

    void Camera::UpdateViewMatrix() {
        auto orientation = glm::quat(glm::radians(m_pitchYawRoll) * glm::vec3(1, -1, -1));
        m_viewMatrix = glm::translate(glm::mat4(1.0f), m_position) * glm::toMat4(orientation);
        m_viewMatrix = glm::inverse(m_viewMatrix);
    }

}
