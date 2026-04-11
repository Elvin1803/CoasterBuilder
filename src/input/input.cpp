#include <pch.h>
#include "input.h"

#include "app.h"
#include "utils/logger.h"

std::map<InputAction, int> Input::m_keymap;
int Input::m_keys[512];

void Input::SetKeybind(InputAction action, int key) {
    LOG_TRACE("set keybind {}", key);
    m_keymap[action] = key;
}

bool Input::IsActionPressed(InputAction action) {
    if (m_keymap.contains(action)) {
        return m_keys[m_keymap[action]];
    }
    return false;
}

void Input::RegisterEvent(const Event& e) {
    if (e.type == EventType::KeyPress || e.type == EventType::MouseButtonPressed) {
        LOG_TRACE("register event {}", e.key);
        m_keys[e.key] = true;
    } else {
        m_keys[e.key] = false;
    }
}

glm::vec2 Input::GetMousePosition() {
    //auto* window = Application::Get().GetWindow().GetNativeWindow();
    auto* window = app::Application::GetApplication().GetWindow().GetWindow();
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return { (float)xpos, (float)ypos };
}

float Input::GetMouseX() {
    return GetMousePosition().x;
}

float Input::GetMouseY() {
    return GetMousePosition().y;
}
