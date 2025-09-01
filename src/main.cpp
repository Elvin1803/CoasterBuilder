#include "renderer.h"
#include "scene/scene.h"
#include "utils/logger.h"
#include "utils/paths.h"
#include "window.h"

int main() {
#ifdef RELEASE
    auto logPath = utils::GetUserDataPath() + "CoasterBuilder.log";
    LOG_CHANGE_OUTPUT(logPath);
#endif

    LOG_TRACE("Starting CoasterBuilder");
    Window window(1280, 720, "CoasterBuilder"); // TODO load config for size
    Renderer renderer(&window);

    scene::Scene scene;
    scene.SpawnModel("test.cbdat");

    while (!window.ShouldClose()) {
        window.PollEvents();

        scene.Update(0); // FIXME

        // Rendering
        renderer.BeginFrame();
        auto& models = scene.GetModels();
        auto& cam = scene.GetCamera();
        renderer.Render(models, cam);
        renderer.EndFrame();

        window.SwapBuffers();
    }

    LOG_TRACE("Exiting CoasterBuilder");
    return 0;
}
