#include "enpch.h"
#include "engine.h"
#include "core/base.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "core/assets/asset_database.h"
#include "core/rendering/window.h"
#include "core/rendering/rendering_api.h"
#include "imgui/imgui_layer.h"
#include "entities/rendering/texture_renderer.h"

namespace engine {
	Engine* Engine::_instance;

	Engine::Engine(const EngineSpecification& specification)
		: _specs(specification) {
		_instance = this;

		AssetDatabase::load_database();

		_window = create_scope<Window>(specification.name);
		ASSERT(_window->init() != -1, "Window creation failed");

		rendering::RenderingAPI::init();

		_imgui_layer = new imgui::ImGuiLayer();
		_editor_layer = new EditorLayer();
		push_overlay(_imgui_layer);
		push_layer(_editor_layer);
	}

	void Engine::run() {
		Ref<Camera> cam = create_ref<Camera>(0.0f, float(_window->get_width()), 0.0f, float(_window->get_height()), -1.0f, 1.0f);

		Ref<Texture> texture = AssetDatabase::load_texture("res/textures/hearth.png");

		Ref<entities::TextureRenderer> tex_renderer = create_ref<entities::TextureRenderer>(texture, Transform(glm::vec2(_window->get_width() * 0.5f, _window->get_height() * 0.5f), 0.0f, glm::vec2(100.0f)));

		rendering::RenderingAPI::set_clear_color(glm::vec4(0.07f, 0.13f, 0.17f, 1.0f));

		while (!_window->should_close()) {
			for (Layer* layer : _layer_stack)
				layer->on_update();

			rendering::RenderingAPI::clear();

			float time = float(glfwGetTime());
			tex_renderer->get_material()->set_vector4("u_Color", glm::vec4(0.5f + sinf(time) * 0.5f, 0.5f + cosf(time) * 0.5f, 0.5f + sinf(time * 3.14f) * 0.5f, 1.0f));

			tex_renderer->draw(cam);

			_imgui_layer->begin();

			for (Layer* layer : _layer_stack)
				layer->on_imgui_render();

			_imgui_layer->end();

			_window->swap_buffers();
			_window->poll_events();
		}
	}

	Engine* Engine::create_engine(EngineCommandLineArgs args) {
		EngineSpecification specification;
		specification.name = "Coal Engine";
		specification.command_line_args = args;
		return new Engine(specification);
	}

	void Engine::push_layer(Layer* layer) {
		_layer_stack.push_layer(layer);
		layer->on_attach();
	}

	void Engine::push_overlay(Layer* layer) {
		_layer_stack.push_overlay(layer);
		layer->on_attach();
	}
}
