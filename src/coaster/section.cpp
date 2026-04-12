#include "section.h"
#include "pch.h"

#include "graphics/graphicsAPI/buffers/buffer.h"
#include "graphics/3d/shaders/trackShader.h"

#include "utils/logger.h"

void Section::SetTrackModel(const graphics::Mesh& mesh) {
    m_model.crosstie = mesh;

    UpdateModel();
}

void Section::Render(const glm::mat4& mvp) {
    graphics::VertexBuffer transformsVBO((float*)m_model.crosstiesTransforms.data(),
                               m_model.crosstiesTransforms.size() * sizeof(glm::mat4),
                               nullptr);

    m_model.crosstie.GetSubMesh().front().vao->Bind();

    for (int i = 0; i < 4; i++) {
        glEnableVertexAttribArray(3 + i);
        glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i * sizeof(glm::vec4)));
        glVertexAttribDivisor(3 + i, 1);
    }

    graphics::TrackShader trackShader;
    trackShader.UseShader();
    trackShader.setMVP(mvp);
    trackShader.setMaterial(m_model.crosstie.GetSubMesh().front().material.get());

    glDrawElementsInstanced(GL_TRIANGLES,
                            m_model.crosstie.GetSubMesh().front().vao->GetIndexLength(),
                            GL_UNSIGNED_INT,
                            0,
                            m_model.crosstiesTransforms.size());
}

void Section::CalculateNodes(ForceData data) {
    // TODO
    (void)data;
}

void Section::CalculateNodes(DirectionData data){
    // TODO
    (void)data;
}

void Section::CalculateNodes(CurveData data) {
    // Reset nodes
    m_nodes.clear();

    // Nodes are max 1 meter apart
    auto numSegments = static_cast<int>(std::ceil(data.length));
    auto stepDist    = data.length / numSegments;

    glm::vec3 worldUp        = glm::vec3(0.f, 1.f, 0.f);

    glm::vec3 currentPos       = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 currentDirection = glm::vec3(1.f, 0.f, 0.f);
    glm::vec3 currentUp        = glm::vec3(0.f, 1.f, 0.f);

    if (prevSection) {
        currentPos       = prevSection->get()->m_nodes.back().position;
        currentDirection = prevSection->get()->m_nodes.back().direction;
        currentUp        = prevSection->get()->m_nodes.back().up;
    }

    auto deltaPitch = glm::radians(data.pitch / numSegments);
    auto deltaYaw   = -glm::radians(data.yaw   / numSegments);
    auto deltaRoll  = glm::radians(data.roll  / numSegments);

    for (int i = 0; i < numSegments; i++) {
        glm::vec3 currentRight;
        if (currentDirection == glm::vec3(0.f, 1.f, 0.f)) {
            currentRight = glm::normalize(glm::cross(currentDirection, worldUp));
        } else {
            currentRight = glm::normalize(glm::cross(currentDirection, currentUp));
        }

        auto rotation     = glm::angleAxis(deltaYaw, worldUp)
                            * glm::angleAxis(deltaPitch, currentRight);

        // Update local vectors
        currentDirection  = glm::normalize(rotation * currentDirection);
        glm::quat rollRot = glm::angleAxis(deltaRoll, currentDirection);
        currentUp         = glm::normalize(rollRot * (rotation * currentUp));

        currentPos += currentDirection * stepDist;

        m_nodes.emplace_back(currentPos, currentDirection, currentUp);
    }

    UpdateModel();
}

void Section::UpdateModel() {
    m_model.crosstiesTransforms.clear();

    for (auto& node : m_nodes) {
        glm::vec3 forward = node.direction;
        glm::vec3 up = node.up;
        glm::vec3 right = glm::normalize(glm::cross(forward, up));

        glm::mat4 rotation = glm::mat4(1.0f);
        rotation[0] = glm::vec4(right, 0.0f);
        rotation[1] = glm::vec4(up, 0.0f);
        rotation[2] = glm::vec4(-forward, 0.0f);

        glm::mat4 translation = glm::translate(glm::mat4(1.0f), node.position);

        m_model.crosstiesTransforms.emplace_back(translation * rotation);
    }
}
