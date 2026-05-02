#include <memory>
#ifdef DEBUG

#include <pch.h>
#include "coaster_scene.h"

#include "coaster/track.h"
#include "coaster/ui/trackEditor.h"

#include "utils/logger.h"

namespace scene {

    CoasterScene::CoasterScene() {
        auto& track = m_tracks.emplace_back();
        track.SetTrackModel("arrow.cbtrack");

        CurveData data{10, 0, 0, 0};
        m_tracks.front().EditSectionData(data);

        m_frames.emplace_back(std::make_unique<UI::TrackEditor>());
        static_cast<UI::TrackEditor*>(m_frames.front().get())->SetTrack(&m_tracks.front());
    }

}

#endif // DEBUG
