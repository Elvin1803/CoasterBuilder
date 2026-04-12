#include <pch.h>
#include "camera.h"

#include "utils/logger.h"
#include "input/input.h"

namespace graphics {

    Camera::Camera(const ViewportRect& rect)
        : m_viewport(rect) {
        UpdateProjectionMatrix();
        UpdateOrbitCameraView();
    }

    void Camera::Update(float timestep) {
        float rotationSpeed = timestep / 1000.f;
        float moveSpeed = timestep / 10000.f;

        // Handle position
        if (Input::IsActionPressed(InputAction::MOVE_FORWARD)) {
            float sinPhi = glm::sin(m_rhoPhiTheta.y);
            float cosPhi = glm::cos(m_rhoPhiTheta.y);
            glm::vec3 forward = glm::vec3(-sinPhi, 0.0f, -cosPhi);
            m_orbitalTarget += forward * moveSpeed;
        }
        if (Input::IsActionPressed(InputAction::MOVE_BACKWARD)) {
            float sinPhi = glm::sin(m_rhoPhiTheta.y);
            float cosPhi = glm::cos(m_rhoPhiTheta.y);
            glm::vec3 forward = glm::vec3(-sinPhi, 0.0f, -cosPhi);
            m_orbitalTarget -= forward * moveSpeed;
        }
        if (Input::IsActionPressed(InputAction::MOVE_LEFT)) {
            float sinPhi = glm::sin(m_rhoPhiTheta.y);
            float cosPhi = glm::cos(m_rhoPhiTheta.y);
            glm::vec3 left = glm::vec3(-cosPhi, 0.0f, sinPhi);
            m_orbitalTarget += left * moveSpeed;
        }
        if (Input::IsActionPressed(InputAction::MOVE_RIGHT)) {
            float sinPhi = glm::sin(m_rhoPhiTheta.y);
            float cosPhi = glm::cos(m_rhoPhiTheta.y);
            glm::vec3 left = glm::vec3(-cosPhi, 0.0f, sinPhi);
            m_orbitalTarget -= left * moveSpeed;
        }
        if (Input::IsActionPressed(InputAction::ZOOM_IN)) {
            m_rhoPhiTheta.x -= moveSpeed;
        }
        if (Input::IsActionPressed(InputAction::ZOOM_OUT)) {
            m_rhoPhiTheta.x += moveSpeed;
        }

        // Handle rotation
        if (Input::IsActionPressed(InputAction::MIDDLE_CLICK)) {
            float m_Xoffset = -(Input::GetMouseX() - m_lastMouseXpos) * rotationSpeed;
            float m_Yoffset = (Input::GetMouseY() - m_lastMouseYpos) * rotationSpeed;

            if (m_rhoPhiTheta.z + m_Yoffset <= glm::half_pi<float>() - 0.01f
                && m_rhoPhiTheta.z + m_Yoffset >= 0.01f) {
                m_rhoPhiTheta.z += m_Yoffset;
            }

            m_rhoPhiTheta.y += m_Xoffset;
        }

        UpdateOrbitCameraView();

        m_lastMouseXpos = Input::GetMouseX();
        m_lastMouseYpos = Input::GetMouseY();
    }

    void Camera::UpdateOrbitCameraView() {
        // Conversion to spherical coordinates
        float x = m_rhoPhiTheta.x * cos(m_rhoPhiTheta.z) * sin(m_rhoPhiTheta.y);
        float y = m_rhoPhiTheta.x * sin(m_rhoPhiTheta.z);
        float z = m_rhoPhiTheta.x * cos(m_rhoPhiTheta.z) * cos(m_rhoPhiTheta.y);

        glm::vec3 cameraPos = m_orbitalTarget + glm::vec3(x, y, z);
        m_viewMatrix = glm::lookAt(cameraPos, m_orbitalTarget, glm::vec3(0.f, 1.f, 0.f));
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
