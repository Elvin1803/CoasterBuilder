#ifndef _APP_H_
#define _APP_H_

#include "input/events.h"
#ifdef DEBUG
#include "scene/graphics_test/gyroscope_scene/gyroscope_scene.h"
#include "scene/graphics_test/texture_scene/texture_scene.h"
#include "scene/coaster_test/coaster_scene.h"
#else
#include "scene/scene.h"
#endif // DEBUG


#include "graphics/renderer.h"
#include "graphics/2d/ui_manager.h"

#include "window.h"

namespace app {

    class Application
    {
    public:
        static Application& GetApplication();

        void Run();

        const Window& GetWindow() { return m_window; };

    private:
        static Application* m_instance;

    private:
        Application();
        ~Application() = default;

        Window m_window{1280, 720, "CoasterBuilder"};
        Renderer m_renderer{&m_window};
        UI::UI_manager m_uiManager{m_window.GetWindow()};

#ifdef DEBUG
        //scene::GyroscopeScene m_scene;
        //scene::TextureScene m_scene;
        scene::CoasterScene m_scene;
#else
        scene::Scene m_scene;
#endif // DEBUG
    };

}

#endif /* _APP_H_ */
