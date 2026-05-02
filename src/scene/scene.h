#ifndef SCENE_H
#define SCENE_H

#include "entity.h"
#include "modelManager.h"

#include "graphics/camera.h"
#include "graphics/2d/frame.h"

#include "coaster/track.h"

namespace scene {

    class Scene {
    public:
        Scene();

        virtual void Update(float timestep);
        void Render();

        graphics::Camera& GetCamera() { return m_camera; };
        std::vector<std::unique_ptr<Entity>>& GetEntities() { return m_entities; };
        std::vector<Track>& GetTracks() { return m_tracks; };
        std::vector<std::unique_ptr<UI::Frame>>& GetFrames() { return m_frames; };

    protected:
        graphics::Camera m_camera;
        std::vector<std::unique_ptr<Entity>> m_entities;
        std::vector<Track> m_tracks;
        std::vector<std::unique_ptr<UI::Frame>> m_frames;

    protected:
        ModelManager m_modelManager;
    };

}

#endif /* SCENE.H */
