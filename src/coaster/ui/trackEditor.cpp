#include "trackEditor.h"

namespace UI{

    void TrackEditor::Render() {
        if (!m_track) return;

        ImGui::Begin("Track Editor");

        ImGui::Text("Section Parameters");
        bool changed = false;
        changed |= ImGui::DragFloat("Length (m)", &m_curveData.length, 0.5f, 4.f, 40.0f);
        changed |= ImGui::DragFloat("Pitch (deg)", &m_curveData.pitch, 0.5f, -90.0f, 90.0f);
        changed |= ImGui::DragFloat("Yaw (deg)", &m_curveData.yaw, 0.5f, -90.0f, 90.0f);
        changed |= ImGui::DragFloat("Roll (deg)", &m_curveData.roll, 0.5f, -180.0f, 180.0f);

        if (changed) {
            m_track->EditSectionData(m_curveData);
        }

        ImGui::Separator();

        if (ImGui::Button("Push section", ImVec2(-1, 30))) {
            m_track->PushSection();
            m_curveData.pitch = 0;
            m_track->EditSectionData(m_curveData);
        }

        if (ImGui::Button("Remove section", ImVec2(-1, 30))) {
            m_track->EraseSection();
        }

        ImGui::End();
    }
}
