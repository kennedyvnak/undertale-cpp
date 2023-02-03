#include "enpch.h"
#include "input.h"

#include "engine.h"

namespace engine {
    bool Input::is_key_pressed(const KeyCode key) {
        auto* window = Engine::get_instance()->get_window().get_ptr();
        auto state = glfwGetKey(window, static_cast<int32_t>(key));
        return state == GLFW_PRESS;
    }

    bool Input::is_mouse_button_pressed(const MouseCode button) {
        auto* window = Engine::get_instance()->get_window().get_ptr();
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::get_mouse_position() {
        auto* window = Engine::get_instance()->get_window().get_ptr();
        double pos_x, pos_y;
        glfwGetCursorPos(window, &pos_x, &pos_y);

        return glm::vec2((float)pos_x, (float)pos_y);
    }

    float Input::get_mouse_y() {
        return get_mouse_position().x;
    }

    float Input::get_mouse_x() {
        return get_mouse_position().y;
    }
}