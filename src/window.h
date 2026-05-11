#ifndef WINDOW_H
#define WINDOW_H

#include "settings.h"

class Window {
public:
    Window(const uint16_t width, const uint16_t height, const std::string &title);
    ~Window();

    Window(const Window& other) = delete;
    Window& operator=(const Window& other) = delete;

    void Resize(uint32_t width, uint32_t height);
    void SetDisplayMode(DisplayMode mode);
    void SetVSync(bool vsync);

    void PollEvents() const;
    bool ShouldClose() const;
    void SwapBuffers() const;

public:
    uint16_t GetWidth() const { return m_width; }
    uint16_t GetHeight() const { return m_height; }
    GLFWwindow* GetWindow() const { return m_window; }

private:
    uint16_t m_width, m_height;
    GLFWwindow *m_window;

private:
    GLFWmonitor* GetCurrentMonitor();
};

#endif /* WINDOW_H */
