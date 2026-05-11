#include <memory>
#ifdef DEBUG

#include <pch.h>
#include "coaster_scene.h"

#include "coaster/track.h"
#include "coaster/ui/trackEditor.h"

namespace scene {

    CoasterScene::CoasterScene() {
        auto& track = m_tracks.emplace_back();
        track.SetTrackModel("arrow.cbtrack");

        CurveData data{10, 0, 0, 0};
        m_tracks.front().EditSectionData(data);

        auto trackEditor = std::make_unique<UI::TrackEditor>();
        trackEditor->SetTrack(&m_tracks.front());
        m_frames.emplace_back(std::move(trackEditor));
    }

}

#endif // DEBUG
