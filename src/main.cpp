#include "app.h"
#include "utils/logger.h"
#include "utils/paths.h"

int main() {
#ifdef RELEASE
    auto logPath = utils::GetUserDataPath() + "CoasterBuilder.log";
    LOG_CHANGE_OUTPUT(logPath);
#endif
    LOG_TRACE("===============================");
    LOG_TRACE("=== Starting CoasterBuilder ===");
    LOG_TRACE("===============================");

    auto& app = app::Application::GetApplication();
    app.Run();

    LOG_TRACE("Exiting CoasterBuilder");
    return 0;
}
