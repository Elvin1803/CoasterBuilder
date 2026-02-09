#include <pch.h>
#include "app.h"

namespace app {

    app_state* app_state::m_instance = nullptr;

    app_state& app_state::GetAppState() {
        if (!m_instance) {
            m_instance = new app_state();
        }

        return *m_instance;
    }

    void app_state::SetFPS(float fps) { m_fps = fps; }

    float app_state::GetFPS() { return m_fps; }
}
