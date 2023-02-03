#pragma once

#include "core/base.h"
#include "texture.h"
#include "camera.h"
#include "core/components/transform.h"

namespace engine {
    class Renderer {
    public:
        static void init();
        static void finalize();

        static void begin_scene(const Ref<Camera>& camera);
        static void end_scene();
        static void end_batch();

        static void draw_quad(const Transform& transform);
        static void draw_quad(const Transform& transform, Ref<Texture> texture);
        static void draw_quad(const Transform& transform, glm::vec4 color);
        static void draw_quad(const Transform& transform, Ref<Texture> texture, glm::vec4 color, float time_offset = 0.0f, float time_speed = 1.0f);

        struct Statistics {
            unsigned int draw_calls = 0;
            unsigned int quad_count = 0;
        };
        static void reset_statistics();
        static Statistics get_stats();
    private:
        static void start_batch();
        static void step_batch();
    };
}