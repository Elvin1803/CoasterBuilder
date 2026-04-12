#include <pch.h>
#include "window.h"

#include "app.h"
#include "utils/logger.h"
#include "input/events.h"
#include "input/input.h"

void GLFWErrorCallback(int error, const char* description) {
    LOG_ERROR("GLFW Error {}: {}", error, description);
}

Window::Window(const uint16_t width, const uint16_t height, const std::string &title)
    : m_width(width), m_height(height) {
    glfwSetErrorCallback(GLFWErrorCallback);

    LOG_INFO("Initializing GLFW");
    if (!glfwInit()) {
        LOG_ERROR("Failed to initialize GLFW");
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!m_window) {
        glfwTerminate();
        LOG_ERROR("Failed to create GLFW window");
        exit(1);
    }

    glfwMakeContextCurrent(m_window);

    // Create OpenGL context
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_FATAL("Failed to initialize GLAD !");
        exit(1);
    }

    glfwSetWindowUserPointer(m_window, this);

    glfwSetKeyCallback(m_window, [](GLFWwindow*, int key, int, int action, int) {
        if (!ImGui::GetIO().WantTextInput) {
            switch (action)
            {
            case GLFW_PRESS:
                Input::RegisterEvent({EventType::KeyPress, key});
                break;
            case GLFW_RELEASE:
                Input::RegisterEvent({EventType::KeyReleased, key});
                break;
            }
        }
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow*, int button, int action, int)
    {
        if (!ImGui::GetIO().WantCaptureMouse) {
            switch (action)
            {
            case GLFW_PRESS:
                Input::RegisterEvent({EventType::MouseButtonPressed, button});
                break;
            case GLFW_RELEASE:
                Input::RegisterEvent({EventType::MouseButtonReleased, button});
                break;
            }
        }
    });

    // TODO: Handle scroll

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
