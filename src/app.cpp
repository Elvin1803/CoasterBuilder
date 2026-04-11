#include <pch.h>
#include "app.h"

#include "input/input.h"
#include "utils/logger.h"

namespace app {

    Application* Application::m_instance = nullptr;

    Application::Application() {
        // TODO: Custom config
        Input::SetKeybind(InputAction::MOVE_FORWARD,  GLFW_KEY_W);
        Input::SetKeybind(InputAction::MOVE_LEFT,     GLFW_KEY_A);
        Input::SetKeybind(InputAction::MOVE_BACKWARD, GLFW_KEY_S);
        Input::SetKeybind(InputAction::MOVE_RIGHT,    GLFW_KEY_D);
        Input::SetKeybind(InputAction::MOVE_UP,       GLFW_KEY_SPACE);
        Input::SetKeybind(InputAction::MOVE_DOWN,     GLFW_KEY_X);
        Input::SetKeybind(InputAction::MOVE_SPRINT,   GLFW_KEY_LEFT_SHIFT);
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
}
