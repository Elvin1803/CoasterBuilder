#include <pch.h>
#include "window.h"

#include "utils/logger.h"

Window::Window(const uint16_t width, const uint16_t height, const std::string &title)
    : m_width(width), m_height(height) {
    if (!glfwInit()) {
        LOG_ERROR("Failed to initialize GLFW");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!m_window) {
        glfwTerminate();
        LOG_ERROR("Failed to create GLFW window");
        return;
    }

    glfwMakeContextCurrent(m_window);

    // Create OpenGL context
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_FATAL("Failed to initialize GLAD !");
    }

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
