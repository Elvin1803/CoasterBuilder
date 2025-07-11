#include "utils/logger.h"
#include "utils/paths.h"

#include "gui/window.h"

int main() {
#ifdef RELEASE
    auto logPath = utils::GetUserDataPath() + "CoasterBuilder.log";
    LOG_CHANGE_OUTPUT(logPath);
#endif

    LOG_TRACE("Starting CoasterBuilder");
    UI::Window window(1280, 720, "CoasterBuilder");

    while (!window.ShouldClose()) {
        window.SwapBuffers();
        window.PollEvents();
    }

    LOG_TRACE("Exiting CoasterBuilder");
    return 0;
}
