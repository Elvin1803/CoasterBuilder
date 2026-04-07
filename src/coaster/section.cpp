#include "section.h"
#include "pch.h"

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

    auto currentPos       = prevSection->get()->m_nodes.back().position;
    auto currentDirection = prevSection->get()->m_nodes.back().direction;
    auto currentUp        = prevSection->get()->m_nodes.back().up;

    auto deltaPitch = glm::radians(data.pitch / numSegments);
    auto deltaYaw   = glm::radians(data.yaw   / numSegments);
    auto deltaRoll  = glm::radians(data.roll  / numSegments);

    for (int i = 0; i < numSegments; i++) {
        // Pitch and yaw
        auto currentRight = glm::normalize(glm::cross(currentDirection, currentUp));
        auto rotation     = glm::angleAxis(deltaPitch, currentRight)
                          * glm::angleAxis(deltaYaw,   currentUp);

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
    // TODO
}
