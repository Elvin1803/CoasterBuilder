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
        Input::SetKeybind(InputAction::MOVE_FORWARD,    GLFW_KEY_W);
        Input::SetKeybind(InputAction::MOVE_LEFT,       GLFW_KEY_A);
        Input::SetKeybind(InputAction::MOVE_BACKWARD,   GLFW_KEY_S);
        Input::SetKeybind(InputAction::MOVE_RIGHT,      GLFW_KEY_D);
        Input::SetKeybind(InputAction::MOVE_UP,         GLFW_KEY_SPACE);
        Input::SetKeybind(InputAction::MOVE_DOWN,       GLFW_KEY_X);
        Input::SetKeybind(InputAction::MOVE_SPRINT,     GLFW_KEY_LEFT_SHIFT);
        Input::SetKeybind(InputAction::SWITCH_CAM_TYPE, GLFW_KEY_T);

        m_settings.resolution = {1920, 1080};
        m_settings.displayMode = DisplayMode::BORDERLESS;
        m_settings.maxFPS = 120;
        ApplyVideoSettings();
    }

    Application& Application::GetApplication() {
        if (!m_instance) {
            m_instance = new Application();
        }

        return *m_instance;
    }

    void Application::Run() {
        auto frameStart = std::chrono::steady_clock::now();
        auto lastTime = std::chrono::steady_clock::now();

        auto lag = 0.f;
        while (!m_window.ShouldClose()) {
            m_window.PollEvents();

            frameStart = std::chrono::steady_clock::now();
            float timestep_ms = std::chrono::duration<float, std::milli>(frameStart - lastTime).count();
            lastTime = frameStart;
            lag += timestep_ms;

            // Fixed timestep update
            while (lag >= 10) {
                m_scene.Update(10);
                lag -= 10;
            }

            // Rendering scene
            m_renderer.BeginFrame();
            m_renderer.Render(m_scene, timestep_ms);
            m_renderer.EndFrame();

            // Rendering UI
            m_uiManager.Render(m_scene);

            m_window.SwapBuffers();

            // cap fps if necessary
            if (m_settings.maxFPS.has_value()) {
                auto timePerFrame = 1000.f / m_settings.maxFPS.value();
                auto frameEnd = std::chrono::steady_clock::now();
                auto elapsedTime = std::chrono::duration<float, std::milli>(frameEnd - frameStart).count();
                if (elapsedTime < timePerFrame) {
                    auto sleepTime = timePerFrame - elapsedTime;

                    if (sleepTime > 16.f) { // because the sleep method on windows can have up to ~15ms delay minimum
                        std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleepTime - 16.f));
                    }

                    while (std::chrono::duration<float, std::milli>(std::chrono::steady_clock::now() - frameStart).count() < timePerFrame) {
                        // this is more precise than the sleep function
                    }
                }
            }

            auto frameEnd = std::chrono::steady_clock::now();
            m_fps = 1000.0f / std::chrono::duration<float, std::milli>(frameEnd - frameStart).count();
        }
    }

    void Application::ApplyVideoSettings() {
        auto width = m_settings.resolution.width;
        auto height = m_settings.resolution.height;

        m_window.Resize(width, height);
        m_renderer.Resize(width, height);
        m_scene.GetCamera().SetViewportRect({0, 0, width, height});

        m_window.SetDisplayMode(m_settings.displayMode);

        m_window.SetVSync(m_settings.vsync);
    }
}
