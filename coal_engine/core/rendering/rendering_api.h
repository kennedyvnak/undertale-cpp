#pragma once

#include <glm/glm.hpp>

namespace engine {
    class RenderingAPI {
    public:
        static void init();

        static void set_clear_color(glm::vec4 color) { _current_api->iset_clear_color(color); }
        static void clear() { _current_api->iclear(); }
        static void enable_depth_test() { _current_api->ienable_depth_test(); }
        static void disable_depth_test() { _current_api->idisable_depth_test(); }
    private:
        RenderingAPI() {}
        ~RenderingAPI() {}

        static RenderingAPI* _current_api;
        glm::vec4 _clear_color;

        void iset_clear_color(glm::vec4 color);
        void iclear();
        void ienable_depth_test();
        void idisable_depth_test();
    };
}
