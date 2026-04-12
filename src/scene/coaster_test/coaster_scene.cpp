#include "scene/scene.h"
#ifdef DEBUG

#include <pch.h>
#include "coaster_scene.h"

#include "coaster/track.h"

#include "utils/logger.h"

namespace scene {

    CoasterScene::CoasterScene() {
        auto& track = m_tracks.emplace_back();
        track.SetTrackModel("arrow.cbtrack");

        m_tracks.front().EditSectionData(data);
    }

    void CoasterScene::Update(float timestep) {
        Scene::Update(timestep);

        ImGui::Begin("Track Editor");

        ImGui::Text("Section Parameters");
        bool changed = false;
        changed |= ImGui::DragFloat("Length (m)", &data.length, 0.5f, 4.f, 40.0f);
        changed |= ImGui::DragFloat("Pitch (deg)", &data.pitch, 0.5f, -90.0f, 90.0f);
        changed |= ImGui::DragFloat("Yaw (deg)", &data.yaw, 0.5f, -90.0f, 90.0f);
        changed |= ImGui::DragFloat("Roll (deg)", &data.roll, 0.5f, -180.0f, 180.0f);

        if (changed) {
            m_tracks.front().EditSectionData(data);
        }

        ImGui::Separator();

        if (ImGui::Button("Push section", ImVec2(-1, 30))) {
            m_tracks.front().PushSection();
            data.pitch = 0;
            m_tracks.front().EditSectionData(data);
        }

        if (ImGui::Button("Remove section", ImVec2(-1, 30))) {
            m_tracks.front().EraseSection();
        }

        ImGui::End();
    }

}

#endif // DEBUG
