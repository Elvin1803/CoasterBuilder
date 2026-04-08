#ifdef DEBUG

#include <pch.h>
#include "coaster_scene.h"

#include "coaster/track.h"

#include "utils/logger.h"

namespace scene {

    CoasterScene::CoasterScene() {
        LOG_TRACE("Coaster Scene constructor");
        m_tracks.emplace_back();
        LOG_TRACE("Set model");
        m_tracks.front().SetTrackModel("arrow.cbtrack");

        m_camera.SetPosition(glm::vec3(15, 1, 10));
    }

    void CoasterScene::Update(float timestep) {
        timer += timestep * clock;

        if (timer > 3600) {
            clock = -1;
        } else if (timer < 0) {
            clock = 1;
        }

        CurveData data(10, timer / 50, 0, timer / 10);
        m_tracks.front().EditSectionData(data);
    }

}

#endif // DEBUG
