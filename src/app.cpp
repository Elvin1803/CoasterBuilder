#include <pch.h>
#include "app.h"

#include "utils/logger.h"

namespace app {

    Application* Application::m_instance = nullptr;

    Application::Application() {
        // TODO: Custom config
    }

    Application& Application::GetApplication() {
        if (!m_instance) {
            m_instance = new Application();
        }

        return *m_instance;
    }

    void Application::Run() {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto lastTime = std::chrono::high_resolution_clock::now();

        float lag = 0;
        while (!m_window.ShouldClose()) {
            m_uiManager.Render();

            currentTime = std::chrono::high_resolution_clock::now();
            float timestep_ms = std::chrono::duration<float, std::milli>(currentTime - lastTime).count();
            lastTime = currentTime;
            lag += timestep_ms;

            //app::app_state::GetAppState().SetFPS(1000.0f / timestep_ms);

            m_window.PollEvents();

            m_scene.Update(10);
            /*
              while (lag >= UPDATE_MS_TICK) {
              scene.Update(UPDATE_MS_TICK);
              lag -= UPDATE_MS_TICK;
              }
            */

            // Rendering
            m_renderer.BeginFrame();
            m_renderer.Render(m_scene);
            m_renderer.EndFrame();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            m_window.SwapBuffers();
        }
    }

    void Application::QueueEvent(std::unique_ptr<Events::Event> e) {
        m_eventQueue.emplace(std::move(e));
        LOG_TRACE("Inserted event");
    }
}
