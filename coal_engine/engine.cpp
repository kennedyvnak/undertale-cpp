#include "enpch.h"
#include "engine.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "core/assets/asset_database.h"
#include "core/rendering/window.h"
#include "core/rendering/rendering_api.h"
#include "core/rendering/renderer.h"
#include "core/rendering/layers/layer.h"
#include "core/os/time.h"
#include "entities/rendering/texture_renderer.h"

namespace engine {
	Engine* Engine::_instance;
	const double EngineMetrics::frame_check_interval = 1.0 / 30.0;

	Engine::Engine(const EngineSpecification& specification)
		: _specs(specification) {
		_instance = this;

		AssetDatabase::load_database();

		_window = create_scope<Window>(specification.name);
		EN_ASSERT(_window->init() != -1, "Window creation failed");

		RenderingAPI::init();
		Renderer::init();

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);
		_framebuffer = create_scope<Framebuffer>(vidmode->width, vidmode->height);
		glViewport(0, 0, vidmode->width, vidmode->height);

#ifndef DISABLE_IMGUI
		_imgui_layer = new imgui::ImGuiLayer();
		push_overlay(_imgui_layer);
#endif
	}

	Engine::~Engine() {
		Renderer::finalize();
	}

	void Engine::run() {
		float ratio = _framebuffer->get_width() / _framebuffer->get_height();

		_camera = create_ref<Camera>(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
		_camera->set_position(glm::vec2(8.0f, 4.5f));

		Ref<Texture> heart_texture = AssetDatabase::load_texture("res/textures/heart.png");
		Ref<Texture> square_texture = AssetDatabase::load_texture("res/textures/square.png");
		Ref<Texture> circle_texture = AssetDatabase::load_texture("res/textures/circle.png");
		Ref<Texture> triangle_texture = AssetDatabase::load_texture("res/textures/triangle.png");
		Ref<Texture> star_texture = AssetDatabase::load_texture("res/textures/star.png");

		Ref<Texture> textures[] = { heart_texture, square_texture, circle_texture, triangle_texture, star_texture };

		for (float y = -7.75f; y < 8.25f; y += 0.5f) {
			for (float x = -7.75f; x < 8.25f; x += 0.5f) {
				glm::vec4 color = { (x + 8.0f) / 16.0f, 0.4f, (y + 4.5f) / 9.0f, 0.65f };
				_texture_renderers.push_back(create_scope<entities::TextureRenderer>(
					textures[rand() % 5],
					Transform(glm::vec2(x, y), sinf(rand()) * 360.0f, glm::vec2(0.45f)), color));
			}
		}

		RenderingAPI::set_clear_color(glm::vec4(0.07f, 0.13f, 0.17f, 1.0f));

		while (!_window->should_close()) {
			calculate_fps();
			Renderer::reset_statistics();

			_framebuffer->bind();
			RenderingAPI::clear();

			Renderer::begin_scene(_camera);

			for (Layer* layer : _layer_stack)
				layer->on_update();

			for (auto& tex_render : _texture_renderers) {
				tex_render->draw();
			}
			Renderer::draw_quad(Transform(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(1.0f, 1.0f)));

			Renderer::end_scene();

			_framebuffer->unbind();

#ifndef DISABLE_IMGUI
			_imgui_layer->begin();

			for (Layer* layer : _layer_stack)
				layer->on_imgui_render();

			_imgui_layer->end();
#endif

			for (Layer* layer : _layer_stack)
				layer->post_render();

			_window->swap_buffers();
			_window->poll_events();
		}
	}

	void Engine::push_layer(Layer* layer) {
		_layer_stack.push_layer(layer);
		layer->on_attach();
	}

	void Engine::push_overlay(Layer* layer) {
		_layer_stack.push_overlay(layer);
		layer->on_attach();
	}

	void Engine::calculate_fps() {
		double current_time = Time::get_time_since_startup_as_double();
		double time_diff = current_time - _fps_previous_time;
		_frame_count++;
		_metrics.total_frame_count++;
		if (time_diff >= EngineMetrics::frame_check_interval) {
			_metrics.fps = _metrics.fps_as_double = 1.0 / time_diff * _frame_count;
			_metrics.ms = _metrics.ms_as_double = time_diff / _frame_count * 1000.0;
			_fps_previous_time = current_time;
			_frame_count = 0;
		}
	}
}
