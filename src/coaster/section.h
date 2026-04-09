#ifndef _SECTION_H_
#define _SECTION_H_

#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "graphics/3d/mesh.h"
#include <vector>

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
    // To calculate direction
    glm::vec3 direction = glm::vec3(1.f, 0.f, 0.f);
    glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);

    float heartline = 0.f;
};

struct TrackModel {
    graphics::Mesh rail;
    graphics::Mesh crosstie;
    std::vector<glm::mat4> crosstiesTransforms;
};

class Section
{
public:
    Section() = default;
    ~Section() = default;

    void SetTrackModel(const graphics::Mesh& mesh);
    void Render(const glm::mat4& mvp);

    virtual void CalculateNodes(ForceData data);
    virtual void CalculateNodes(DirectionData data);
    void CalculateNodes(CurveData data);

    std::unique_ptr<Section>* prevSection = nullptr;
    std::unique_ptr<Section>* nextSection = nullptr;

private:
    void UpdateModel();

private:
    std::vector<TrackNode> m_nodes;
    TrackModel m_model;
};


#endif /* _SECTION_H_ */
