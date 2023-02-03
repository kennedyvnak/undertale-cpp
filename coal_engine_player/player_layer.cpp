#if ENGINE_PLAYER
#include "player_layer.h"
#include "core/events/window_event.h"

namespace engine::player {
    PlayerLayer::PlayerLayer(const std::string& name)
        : Layer(name) {
        framebuffer_shader = AssetDatabase::load_shader("res/shaders/main_framebuffer.glsl");

        framebuffer_va = create_ref<VertexArray>();

        float* rectangle_vertices = new float[] {
            -1.0f, -1.0f, 0.0f, 0.0f,
                1.0f, -1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, 0.0f, 1.0f
        };

        framebuffer_vb = create_ref<VertexBuffer>(16 * static_cast<unsigned int>(sizeof(float)), rectangle_vertices, false);
        framebuffer_vb->set_layout({
            { UniformType::Vec2, "a_Position" },
            { UniformType::Vec2, "a_TexCoord" },
            });
        framebuffer_va->add_vertex_buffer(framebuffer_vb);

        delete[] rectangle_vertices;

        unsigned int* rectangle_indices = new unsigned int[] {
            0, 1, 2,
                2, 3, 0
        };

        framebuffer_ib = create_ref<IndexBuffer>(rectangle_indices, 6);
        framebuffer_va->set_index_buffer(framebuffer_ib);
        delete[] rectangle_indices;
    }

    void PlayerLayer::on_attach() {
        auto& fb = Engine::get_instance()->get_framebuffer();
        auto& texture = fb.get_texture();

        framebuffer_shader->bind();
        framebuffer_shader->set_uniform_int("u_Texture", 0);
    }

    void PlayerLayer::post_render() {
        auto& fb = Engine::get_instance()->get_framebuffer();
        fb.get_texture().bind(0);
        framebuffer_shader->bind();
        framebuffer_va->bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    bool PlayerLayer::on_event(Event& event) {
        EventDispatcher dispatcher(event);
        return dispatcher.dispatch<WindowResizeEvent>(EN_BIND_EVENT_FUNC(PlayerLayer::on_window_resize));
    }

    bool PlayerLayer::on_window_resize(WindowResizeEvent& event) {
        Engine::get_instance()->resize_viewport(event.get_width(), event.get_height());
        return false;
    }
}
#endif // ENGINE_PLAYER
