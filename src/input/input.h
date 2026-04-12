#ifndef _INPUT_H_
#define _INPUT_H_

#include "events.h"

enum class InputAction {
    MOVE_FORWARD, MOVE_BACKWARD, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, MOVE_SPRINT,

    // These actions key cannot be changed
    LEFT_CLICK, RIGHT_CLICK, MIDDLE_CLICK,
    ZOOM_IN, ZOOM_OUT,
};

class Input {
public:
    static void SetKeybind(InputAction action, int key);
    static bool IsActionPressed(InputAction action);

    static void RegisterEvent(const Event& e);

    static glm::vec2 GetMousePosition();
    static float GetMouseX();
    static float GetMouseY();

private:
    static std::map<InputAction, int> m_keymap;
    static int m_keys[512]; // Should never exceed this size
};

#endif /* _INPUT_H_ */
