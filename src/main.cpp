#include "graphics/renderer.h"
#include "utils/logger.h"
#include "utils/paths.h"
#include "window.h"

#ifdef DEBUG
#include "scene/graphics_test/gyroscope_scene/gyroscope_scene.h"
#include "scene/graphics_test/texture_scene/texture_scene.h"
#else
#include "scene/scene.h"
#endif // DEBUG

// FIXME: Maybe don't use a macro for this, idk
#define UPDATE_MS_TICK (10)

int main() {
#ifdef RELEASE
    auto logPath = utils::GetUserDataPath() + "CoasterBuilder.log";
    LOG_CHANGE_OUTPUT(logPath);
#endif

    LOG_TRACE("===============================");
    LOG_TRACE("=== Starting CoasterBuilder ===");
    LOG_TRACE("===============================");
    Window window(1280, 720, "CoasterBuilder"); // TODO load config for size
    Renderer renderer(&window);

#ifdef DEBUG
    //scene::GyroscopeScene scene;
    scene::TextureScene scene;
#else
    scene::Scene scene;
#endif // DEBUG

    auto currentTime = std::chrono::high_resolution_clock::now();
    auto lastTime = std::chrono::high_resolution_clock::now();
    float lag = 0;
    while (!window.ShouldClose()) {
        currentTime = std::chrono::high_resolution_clock::now();
        float timestep_ms = std::chrono::duration<float, std::milli>(currentTime - lastTime).count();
        lastTime = currentTime;
        lag += timestep_ms;
        LOG_TRACE("FPS: {}", 1000.0f / timestep_ms);

        window.PollEvents();

        while (lag >= UPDATE_MS_TICK) {
            scene.Update(UPDATE_MS_TICK);
            lag -= UPDATE_MS_TICK;
        }

        // Rendering
        renderer.BeginFrame();
        renderer.Render(scene);
        renderer.EndFrame();

        window.SwapBuffers();
    }

    LOG_TRACE("Exiting CoasterBuilder");
    return 0;
}
