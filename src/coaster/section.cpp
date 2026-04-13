#include "section.h"
#include "pch.h"

#include "bspline.h"

#include "graphics/graphicsAPI/buffers/buffer.h"
#include "graphics/3d/shaders/trackShader.h"

#include "utils/logger.h"

void Section::SetTrackModel(const graphics::TrackModel& trackModel) {
    m_model = trackModel;

    UpdateModel();
}

void Section::Render(const glm::mat4& mvp, bool isCurrent) {
    graphics::VertexBuffer transformsVBO((float*)m_modelTransforms.data(),
                               m_modelTransforms.size() * sizeof(glm::mat4),
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
    trackShader.setMaterial(m_model.crosstie.GetSubMesh().front().material.get(), isCurrent);

    glDrawElementsInstanced(GL_TRIANGLES,
                            m_model.crosstie.GetSubMesh().front().vao->GetIndexLength(),
                            GL_UNSIGNED_INT,
                            0,
                            m_modelTransforms.size());
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
    if (prevSection) {
        prevSection->get()->UpdateModel();
    }
}

void Section::UpdateModel() {
    m_modelTransforms.clear();

    auto crosstiesStepDist = 1.5f; // 1.5 m
    auto accumulatedDist = 0.0f;
    glm::vec3 lastPos;

    auto constructSpline = [&](const TrackNode& n0, const TrackNode& n1,
                               const TrackNode& n2, const TrackNode& n3) {
        float t = 0;
        while (t < 1.f) {
            t += 0.005f;
            auto currentPos = calculateBSpline(n0.position,
                                               n1.position,
                                               n2.position,
                                               n3.position,
                                               t);
            auto currentDir = calculateBSpline(n0.direction,
                                               n1.direction,
                                               n2.direction,
                                               n3.direction,
                                               t);
            auto currentUp = calculateBSpline(n0.up,
                                              n1.up,
                                              n2.up,
                                              n3.up,
                                              t);

            auto d = glm::distance(lastPos, currentPos);
            lastPos = currentPos;
            accumulatedDist += d;

            if (accumulatedDist >= crosstiesStepDist) {
                auto currentRight = glm::normalize(glm::cross(currentDir, currentUp));

                glm::mat4 rotation = glm::mat4(1.0f);
                rotation[0] = glm::vec4(currentRight, 0.0f);
                rotation[1] = glm::vec4(currentUp, 0.0f);
                rotation[2] = glm::vec4(-currentDir, 0.0f);

                glm::mat4 translation = glm::translate(glm::mat4(1.0f), currentPos);

                m_modelTransforms.emplace_back(translation * rotation);

                accumulatedDist -= crosstiesStepDist;
            }
        }
    };

    if (prevSection) {
        lastPos = calculateBSpline(prevSection->get()->m_nodes.back().position,
                                   m_nodes[0].position,
                                   m_nodes[1].position,
                                   m_nodes[2].position,
                                   0.5f);
        constructSpline(prevSection->get()->m_nodes.back(), m_nodes[0],
                        m_nodes[1], m_nodes[2]);
    } else {
        lastPos = calculateBSpline(m_nodes[0].position,
                                   m_nodes[1].position,
                                   m_nodes[2].position,
                                   m_nodes[3].position,
                                   0);
    }

    for (size_t i = 0; i < m_nodes.size() - 3; i++) {
        constructSpline(m_nodes[i], m_nodes[i + 1], m_nodes[i + 2], m_nodes[i + 3]);
    }

    if (nextSection) {
        auto temp = m_nodes.size() - 3;
        constructSpline(m_nodes[temp], m_nodes[temp + 1],
                        m_nodes[temp + 2], nextSection->get()->m_nodes[0]);
        constructSpline(m_nodes[temp + 1], m_nodes[temp + 2],
                        nextSection->get()->m_nodes[0], nextSection->get()->m_nodes[1]);
    }
}
