#include "renderer.h"
#include "utils/logger.h"
#include "utils/paths.h"
#include "window.h"

#ifdef DEBUG
#include "scene/graphics_test/gyroscope_scene/gyroscope_scene.h"
#include "scene/graphics_test/texture_scene/texture_scene.h"
#else
#include "scene/scene.h"
#endif // DEBUG

int main() {
#ifdef RELEASE
    auto logPath = utils::GetUserDataPath() + "CoasterBuilder.log";
    LOG_CHANGE_OUTPUT(logPath);
#endif

    LOG_TRACE("Starting CoasterBuilder");
    Window window(1280, 720, "CoasterBuilder"); // TODO load config for size
    Renderer renderer(&window);

#ifdef DEBUG
    //scene::GyroscopeScene scene;
    scene::TextureScene scene;
#else
    scene::Scene scene;
#endif // DEBUG

    while (!window.ShouldClose()) {
        window.PollEvents();

        scene.Update(0); // FIXME

        // Rendering
        renderer.BeginFrame();
        renderer.Render(scene);
        renderer.EndFrame();

        window.SwapBuffers();
    }

    LOG_TRACE("Exiting CoasterBuilder");
    return 0;
}
