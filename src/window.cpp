#include <pch.h>
#include "window.h"

#include "settings.h"
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

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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

void Window::Resize(uint32_t width, uint32_t height) {
    m_width = width;
    m_height = height;
    glfwSetWindowSize(m_window, width, height);
}

void Window::SetDisplayMode(DisplayMode mode){
    GLFWmonitor* monitor = GetCurrentMonitor();
    const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);

    const auto centerX = (vidMode->width - m_width) / 2;
    const auto centerY = (vidMode->height - m_height) / 2;

    switch (mode)
    {
    case DisplayMode::BORDERLESS:
    {
        glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_FALSE);
        glfwSetWindowPos(m_window, centerX, centerY);
        break;
    }
    case DisplayMode::WINDOWED:
    {
        glfwSetWindowAttrib(m_window, GLFW_DECORATED, GLFW_TRUE);
        glfwSetWindowPos(m_window, centerX, centerY + 10);
        break;
    }
    default:
        return;
    }
}

void Window::SetVSync(bool vsync) {
    vsync ? glfwSwapInterval(1) : glfwSwapInterval(0);
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

GLFWmonitor* Window::GetCurrentMonitor() {
    int nbMonitors;
    GLFWmonitor** monitors = glfwGetMonitors(&nbMonitors);

    int wx, wy;
    glfwGetWindowPos(m_window, &wx, &wy);

    GLFWmonitor* mainMonitor = nullptr;
    int maxOverlap = 0;

    for (int i = 0; i < nbMonitors; i++) {
        const GLFWvidmode* mode = glfwGetVideoMode(monitors[i]);
        int mx, my;
        glfwGetMonitorPos(monitors[i], &mx, &my);

        int mw = mode->width;
        int mh = mode->height;

        // Calculate overlap area
        int overlap = std::max(0, std::min(wx + m_width, mx + mw) - std::max(wx, mx)) *
                      std::max(0, std::min(wy + m_height, my + mh) - std::max(wy, my));

        if (overlap > maxOverlap) {
            maxOverlap = overlap;
            mainMonitor = monitors[i];
        }
    }
    return mainMonitor;
}
