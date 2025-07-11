#include <pch.h>
#include "window.h"

#include "utils/logger.h"

namespace UI {

    Window::Window(const uint16_t width, const uint16_t height, const std::string &title) {
        if (!glfwInit()) {
            LOG_ERROR("Failed to initialize GLFW");
            return;
        }

        m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        if (!m_window) {
            glfwTerminate();
            LOG_ERROR("Failed to create GLFW window");
            return;
        }

        glfwMakeContextCurrent(m_window);
    }

    Window::~Window() {
        if (m_window) {
            glfwDestroyWindow(m_window);
        }

        glfwTerminate();
    }

    void Window::PollEvents() const {
        glfwPollEvents();
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(m_window);
    }

    void Window::SwapBuffers() const {
        glfwSwapBuffers(m_window);
    }

} // namespace UI
