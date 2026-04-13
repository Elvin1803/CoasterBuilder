#ifndef _TRACK_H_
#define _TRACK_H_

#include "section.h"

#include "graphics/3d/model.h"

class Track {
public:
    Track();

    void SetTrackModel(const std::string& filename);
    void Render(const glm::mat4& mvp);

    // Will push a new section after the currentSection, and set the
    // current section to the new one.
    void PushSection();
    void EraseSection();
    void SetCurrentSection(std::unique_ptr<Section>* section);

    void EditSectionType(SectionType type);

    void EditSectionData(ForceData data) { m_currentSection->get()->CalculateNodes(data); };
    void EditSectionData(DirectionData data) { m_currentSection->get()->CalculateNodes(data); };
    void EditSectionData(CurveData data) { m_currentSection->get()->CalculateNodes(data); };

private:
    float friction = 1.f;
    std::list<std::unique_ptr<Section>> m_sections; // 1 section = 1 mesh
    std::unique_ptr<Section>* m_currentSection = nullptr; // Section that is being edited

    graphics::TrackModel m_trackModel;
};


#endif /* _TRACK_H_ */
