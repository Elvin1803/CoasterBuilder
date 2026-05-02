#include <pch.h>
#include "app.h"

#include "GLFW/glfw3.h"
#include "input/input.h"
#include "utils/logger.h"

namespace app {

    Application* Application::m_instance = nullptr;

    Application::Application() {
        Input::SetKeybind(InputAction::LEFT_CLICK,   GLFW_MOUSE_BUTTON_LEFT);
        Input::SetKeybind(InputAction::RIGHT_CLICK,  GLFW_MOUSE_BUTTON_RIGHT);
        Input::SetKeybind(InputAction::MIDDLE_CLICK, GLFW_MOUSE_BUTTON_MIDDLE);
        Input::SetKeybind(InputAction::ZOOM_OUT,     GLFW_KEY_LEFT_CONTROL);
        Input::SetKeybind(InputAction::ZOOM_IN,      GLFW_KEY_LEFT_SHIFT);


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
            m_window.PollEvents();

            currentTime = std::chrono::high_resolution_clock::now();
            float timestep_ms = std::chrono::duration<float, std::milli>(currentTime - lastTime).count();
            lastTime = currentTime;
            lag += timestep_ms;

            m_fps = 1000.0f / timestep_ms;

            while (lag >= 10) {
              m_scene.Update(10);
              lag -= 10;
            }

            // Rendering scene
            m_renderer.BeginFrame();
            m_renderer.Render(m_scene);
            m_renderer.EndFrame();

            // Rendering UI
            m_uiManager.Render(m_scene);

            m_window.SwapBuffers();
        }
    }
}
