#include "app.h"
#include "graphics/renderer.h"
#include "graphics/2d/ui_manager.h"
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

    UI::UI_manager ui(window.GetWindow());

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
        ui.Render();

        currentTime = std::chrono::high_resolution_clock::now();
        float timestep_ms = std::chrono::duration<float, std::milli>(currentTime - lastTime).count();
        lastTime = currentTime;
        lag += timestep_ms;

        app::app_state::GetAppState().SetFPS(1000.0f / timestep_ms);

        window.PollEvents();

        while (lag >= UPDATE_MS_TICK) {
            scene.Update(UPDATE_MS_TICK);
            lag -= UPDATE_MS_TICK;
        }

        // Rendering
        renderer.BeginFrame();
        renderer.Render(scene);
        renderer.EndFrame();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.SwapBuffers();
    }

    LOG_TRACE("Exiting CoasterBuilder");
    return 0;
}
