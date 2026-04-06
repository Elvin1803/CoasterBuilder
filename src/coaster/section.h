#ifndef _SECTION_H_
#define _SECTION_H_

#include "graphics/3d/mesh.h"

enum class SectionType { Basic, Station, Lift, Brake };

// G forces
struct ForceData {
    float time; // seconds
    float vertical;
    float lateral;
    float rollPerSec; // degree per second
};

// degrees per second
struct DirectionData {
    float time; // seconds
    float pitch;
    float yaw;
    float roll;
};

// degree per meter
struct CurveData {
    float length; // meters
    float pitch;
    float yaw;
    float roll;
};

// y is up vector
struct TrackNode {
    // Editable
    glm::vec3 position = glm::vec3(0.f, 0.f, 0.f); // world space
    // local direction
    glm::vec3 forward = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 up = glm::vec3(0.f, 0.f, 0.f);

    std::optional<float> heartline = std::nullopt; // Take coaster heartline by default
};

class Section
{
public:
    Section();
    ~Section();

    virtual void CalculateNodes(ForceData data);
    virtual void CalculateNodes(DirectionData data);
    virtual void CalculateNodes(CurveData data);

    std::unique_ptr<Section>* prevSection = nullptr;
    std::unique_ptr<Section>* nextSection = nullptr;

private:
    void UpdateModel();

private:
    std::vector<TrackNode> m_nodes;
    std::shared_ptr<graphics::Mesh> m_mesh;
};


#endif /* _SECTION_H_ */
