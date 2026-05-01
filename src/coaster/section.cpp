#include "section.h"
#include "graphics/3d/shaders/simpleShader.h"
#include "pch.h"

#include "bspline.h"

#include "graphics/graphicsAPI/buffers/buffer.h"
#include "graphics/3d/shaders/trackShader.h"

#include "utils/logger.h"

const std::shared_ptr<graphics::BufferLayout> Section::railsBufferLayout =
    std::make_shared<graphics::BufferLayout>(
        std::vector<graphics::BufferLayoutElement>{
            { 3, graphics::ShaderDataType::Float }, // Position
            { 3, graphics::ShaderDataType::Float }, // Normal
            { 2, graphics::ShaderDataType::Float }, // Texture coordinates
        });

void Section::SetTrackModel(const graphics::TrackModel& trackModel) {
    m_model = trackModel;

    UpdateModel();
}

void Section::Render(const glm::mat4& mvp, bool isCurrent) {
    graphics::TrackShader trackShader;
    trackShader.UseShader();
    trackShader.setMVP(mvp);
    trackShader.setInstancing(false);
    trackShader.setMaterial(m_model.crosstie.GetSubMesh().front().material.get(), isCurrent);

    m_railsModel.GetSubMesh().front().vao->Bind();
    glDrawElements(GL_TRIANGLES, m_railsModel.GetSubMesh().front().vao->GetIndexLength(), GL_UNSIGNED_INT, 0);

    trackShader.setInstancing(true);
    graphics::VertexBuffer transformsVBO((float*)m_modelTransforms.data(),
                               m_modelTransforms.size() * sizeof(glm::mat4),
                               nullptr);

    m_model.crosstie.GetSubMesh().front().vao->Bind();

    for (int i = 0; i < 4; i++) {
        glEnableVertexAttribArray(3 + i);
        glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i * sizeof(glm::vec4)));
        glVertexAttribDivisor(3 + i, 1);
    }

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
    auto stepDist    = (data.length / numSegments);

    glm::vec3 worldUp        = glm::vec3(0.f, 1.f, 0.f);

    glm::vec3 currentPos       = glm::vec3(-stepDist, 0.f, 0.f);
    glm::vec3 currentDirection = glm::vec3(1.f,       0.f, 0.f);
    glm::vec3 currentUp        = glm::vec3(0.f,       1.f, 0.f);
    if (prevSection) {
        const auto& temp = prevSection->get()->m_nodes[prevSection->get()->m_nodes.size() - 2];
        m_nodes.emplace_back(temp.position, temp.direction, temp.up);

        currentPos       = prevSection->get()->m_nodes.back().position;
        currentDirection = prevSection->get()->m_nodes.back().direction;
        currentUp        = prevSection->get()->m_nodes.back().up;
        m_nodes.emplace_back(currentPos, currentDirection, currentUp);
    } else { // This is because of b-splines
        m_nodes.emplace_back(currentPos, currentDirection, currentUp);

        currentPos += currentDirection * stepDist;
        m_nodes.emplace_back(currentPos, currentDirection, currentUp);
    }

    auto deltaPitch = glm::radians(data.pitch / numSegments);
    auto deltaYaw   = -glm::radians(data.yaw  / numSegments);
    auto deltaRoll  = glm::radians(data.roll  / numSegments);

    for (int i = 0; i < numSegments; i++) {
        glm::vec3 currentRight;
        if (currentDirection == glm::vec3(0.f, 1.f, 0.f)) {
            currentRight = glm::normalize(glm::cross(currentDirection, worldUp));
        } else {
            currentRight = glm::normalize(glm::cross(currentDirection, currentUp));
        }

        auto rotation = glm::angleAxis(deltaYaw, worldUp) * glm::angleAxis(deltaPitch, currentRight);

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

    std::vector<float> railVertices;
    std::vector<uint32_t> railIndices;
    uint32_t currentIdx = 0;

    auto accumulatedDist = 0.0f;
    glm::vec3 lastPos;

    auto constructSpline = [&](const TrackNode& n0, const TrackNode& n1,
                               const TrackNode& n2, const TrackNode& n3, bool end) {
        float t = 0;
        float limit = end ? 1.1f : 1.f;
        while (t < limit) {
            t += 0.1f;
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
            auto currentRight = glm::normalize(glm::cross(currentDir, currentUp));

            auto rotation = glm::mat4(1.0f);
            rotation[0] = glm::vec4(currentRight, 0.0f);
            rotation[1] = glm::vec4(currentUp, 0.0f);
            rotation[2] = glm::vec4(-currentDir, 0.0f);
            auto translation = glm::translate(glm::mat4(1.0f), currentPos);
            auto transformMat = translation * rotation;

            // je pleure
            // on genere le rail...
            size_t nbVertices = m_model.railProfile.size() / 3; // magic nb go brrr

            for (size_t i = 0; i < m_model.railProfile.size(); i += 3) {
                glm::vec4 pos = transformMat
                    * glm::vec4(m_model.railProfile[i], m_model.railProfile[i+1], m_model.railProfile[i+2], 1.0f);

                // Position
                railVertices.push_back(pos.x); railVertices.push_back(pos.y); railVertices.push_back(pos.z);
                // Normals
                railVertices.push_back(0); railVertices.push_back(0); railVertices.push_back(0);
                // UV Coords
                railVertices.push_back(0); railVertices.push_back(0);
            }

            if (currentIdx > 0) {
                size_t prevIdx = currentIdx - nbVertices;

                for (size_t i = 0; i < m_model.railIndices.size(); i += 2) {
                    // FIXME: backface culling problems...
                    railIndices.push_back(prevIdx + m_model.railIndices[i]);
                    railIndices.push_back(prevIdx + m_model.railIndices[i + 1]);
                    railIndices.push_back(currentIdx + m_model.railIndices[i]);

                    railIndices.push_back(prevIdx + m_model.railIndices[i + 1]);
                    railIndices.push_back(currentIdx + m_model.railIndices[i + 1]);
                    railIndices.push_back(currentIdx + m_model.railIndices[i]);
                }
            }
            currentIdx += nbVertices;

            // Check if crosstie needs to be placed
            auto d = glm::distance(lastPos, currentPos);
            accumulatedDist += d;
            if (accumulatedDist >= m_crosstiesStepDist) {
                m_modelTransforms.push_back(transformMat);
                accumulatedDist -= m_crosstiesStepDist;
            }

            lastPos = currentPos;
        }
    };

    if (prevSection) {
        lastPos = (prevSection->get()->m_modelTransforms.back()[3]);
        constructSpline(prevSection->get()->m_nodes[prevSection->get()->m_nodes.size() - 3],
                        m_nodes[0],
                        m_nodes[1],
                        m_nodes[2], false);
    } else {
        lastPos = calculateBSpline(m_nodes[0].position,
                                   m_nodes[1].position,
                                   m_nodes[2].position,
                                   m_nodes[3].position,
                                   0);
    }

    for (size_t i = 0; i < m_nodes.size() - 4; i += 1) {
        constructSpline(m_nodes[i], m_nodes[i + 1], m_nodes[i + 2], m_nodes[i + 3], false);
    }
    constructSpline(m_nodes[m_nodes.size() - 4],
                    m_nodes[m_nodes.size() - 3],
                    m_nodes[m_nodes.size() - 2],
                    m_nodes[m_nodes.size() - 1], true);

    std::unique_ptr<graphics::VertexBuffer> vbo =
        std::make_unique<graphics::VertexBuffer>(railVertices.data(),
                                                 railVertices.size() * sizeof(float), railsBufferLayout);
    std::unique_ptr<graphics::IndexBuffer> ibo =
        std::make_unique<graphics::IndexBuffer>(railIndices.data(), railIndices.size() * sizeof(uint32_t));
    const std::shared_ptr<graphics::VertexArray> vao =
        std::make_shared<graphics::VertexArray>(std::move(vbo), std::move(ibo));

    m_railsModel.Reset();
    m_railsModel.AddSubMesh(vao);
}
