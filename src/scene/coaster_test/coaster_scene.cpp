#ifdef DEBUG

#include <pch.h>
#include "coaster_scene.h"

#include "coaster/track.h"
#include "coaster/ui/trackEditor.h"

namespace scene {

    CoasterScene::CoasterScene() {
        auto& track = m_tracks.emplace_back();
        track.SetTrackModel("ng_vekoma.cbtrack");

        CurveData data{10, 0, 0, 0};
        m_tracks.front().EditSectionData(data);

        auto trackEditor = std::make_unique<UI::TrackEditor>();
        trackEditor->SetTrack(&m_tracks.front());
        m_frames.emplace_back(std::move(trackEditor));

        // coaster train
        auto nose_model = m_modelManager.GetModel("surf_coaster_nose.cbmodel");
        graphics::ModelInstance modelInstance(nose_model);
        m_entities.emplace_back(std::make_unique<PlaceHolderModel>(modelInstance));
    }

}

#endif // DEBUG
