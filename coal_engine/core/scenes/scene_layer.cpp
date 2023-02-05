#include "enpch.h"
#include "scene_layer.h"
#include "core/assets/asset_database.h"
#include "engine.h"

namespace engine {
    void SceneLayer::on_attach() {
        auto& game_viewport = Engine::get_instance()->get_viewport();
        _camera = create_ref<Camera>((float)game_viewport.get_width() / (float)game_viewport.get_height());
        Camera::set_scene_camera(_camera);

        Ref<Texture> heart_texture = AssetDatabase::load_texture("res/textures/heart.png");
        Ref<Texture> square_texture = AssetDatabase::load_texture("res/textures/square.png");
        Ref<Texture> circle_texture = AssetDatabase::load_texture("res/textures/circle.png");
        Ref<Texture> triangle_texture = AssetDatabase::load_texture("res/textures/triangle.png");
        Ref<Texture> star_texture = AssetDatabase::load_texture("res/textures/star.png");

        Ref<Texture> textures[] = { heart_texture, square_texture, circle_texture, triangle_texture, star_texture };

        for (float y = -7.75f; y < 8.25f; y += 0.5f) {
            for (float x = -7.75f; x < 8.25f; x += 0.5f) {
                glm::vec4 color = { (x + 8.0f) / 16.0f, 0.4f, (y + 4.5f) / 9.0f, 0.9f };
                _texture_renderers.push_back(create_scope<entities::TextureRenderer>(
                    textures[rand() % 5],
                    Transform(glm::vec2(x, y), 0.0f, glm::vec2(0.475f)), color));
            }
        }
    }

    void SceneLayer::on_update() {
        for (auto& tex_render : _texture_renderers) {
            tex_render->update();
        }
    }

    void SceneLayer::render() {
        for (auto& tex_render : _texture_renderers) {
            tex_render->draw();
        }
    }

    bool SceneLayer::on_event(Event& event) {
        EventDispatcher dispatcher(event);
        return dispatcher.dispatch<EngineResizeViewportEvent>(EN_BIND_EVENT_FUNC(SceneLayer::on_resize_viewport));
    }

    bool SceneLayer::on_resize_viewport(EngineResizeViewportEvent& event) {
        _camera->set_aspect_ratio((float)event.get_width() / (float)event.get_height());
        return false;
    }
}
