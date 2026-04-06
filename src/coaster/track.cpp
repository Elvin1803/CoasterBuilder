#include "track.h"
#include <pch.h>

#include "stationSection.h"

Track::Track() {
    // Add station section
    m_currentSection = &m_sections.emplace_back(std::make_unique<StationSection>());
    // 3 meters per second
    static_cast<StationSection*>(m_currentSection->get())->SetExitSpeed(3.f);
    // 10 meter straight section
    CurveData data{10, 0, 0, 0};
    EditSectionData(data);

    PushSection();
}

void Track::PushSection() {
    auto* newSection = &m_sections.emplace_back(std::make_unique<Section>());
    m_currentSection->get()->nextSection = newSection;
    newSection->get()->prevSection = m_currentSection;
    m_currentSection = newSection;
}

void Track::SetCurrentSection(std::unique_ptr<Section>* section) {
    m_currentSection = section;
    // TODO: Change material for rendering
}

void Track::EditSectionType(SectionType type) {
    // TODO
    (void)type;
};
