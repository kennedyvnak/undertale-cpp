#pragma once

#include <glm/glm.hpp>

namespace engine::rendering {
    class RenderingAPI {
    public:
        static void init();

        static void set_clear_color(glm::vec4 color) { _current_api->iset_clear_color(color); }
        static void clear() { _current_api->iclear(); }

    private:
        RenderingAPI() {}
        ~RenderingAPI() {}

        static RenderingAPI* _current_api;
        glm::vec4 _clear_color;

        void iset_clear_color(glm::vec4 color);
        void iclear();
    };
}