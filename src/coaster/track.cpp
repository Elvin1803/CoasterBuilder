#include "track.h"
#include <pch.h>

#include "stationSection.h"
#include "graphics/3d/modelLoader.h"

#include "utils/logger.h"

Track::Track() {
    // Add station section
    m_currentSection = &m_sections.emplace_back(std::make_unique<StationSection>());
    // 3 meters per second
    static_cast<StationSection*>(m_currentSection->get())->SetExitSpeed(3.f);
    // 10 meter straight section
    CurveData data{30, 0, 0, 0};
    EditSectionData(data);

    PushSection();
}

void Track::SetTrackModel(const std::string& filename) {
    m_trackModel = graphics::modelLoader::LoadTrack(filename);

    for (auto& section : m_sections) {
        section->SetTrackModel(m_trackModel);
    }
}

void Track::Render(const glm::mat4& mvp) {
    for (auto& section : m_sections) {
        section->Render(mvp, m_currentSection->get() == section.get());
    }
}

void Track::PushSection() {
    auto* newSection = &m_sections.emplace_back(std::make_unique<Section>());
    m_currentSection->get()->nextSection = newSection;
    newSection->get()->prevSection = m_currentSection;
    SetCurrentSection(newSection);
}

void Track::EraseSection() {
    if (m_currentSection->get()->prevSection) {
        m_currentSection->get()->prevSection->get()->nextSection = m_currentSection->get()->nextSection;
    }

    if (m_currentSection->get()->nextSection) {
        m_currentSection->get()->nextSection->get()->prevSection = m_currentSection->get()->prevSection;
    }

    auto temp = m_currentSection->get()->prevSection;
    m_sections.remove(*m_currentSection);
    m_currentSection = temp;
}

void Track::SetCurrentSection(std::unique_ptr<Section>* section) {
    m_currentSection = section;
    if (section) {
        CurveData data{10, 0, 0, 0};
        EditSectionData(data);
        LOG_TRACE("Edited section data");
        m_currentSection->get()->SetTrackModel(m_trackModel);
        LOG_TRACE("Set track model");
        // TODO: Change material for rendering
    }
}

void Track::EditSectionType(SectionType type) {
    // TODO
    (void)type;
};
