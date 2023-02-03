#pragma once

#include "key_codes.h"
#include "mouse_codes.h"

#include <glm/glm.hpp>

namespace engine {
    class Input {
        public:
        static bool is_key_pressed(KeyCode key);

        static bool is_mouse_button_pressed(MouseCode button);
        static glm::vec2 get_mouse_position();
        static float get_mouse_x();
        static float get_mouse_y();
    };
}