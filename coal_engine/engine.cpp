#include "enpch.h"
#include "engine.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "core/assets/asset_database.h"
#include "core/rendering/window.h"
#include "core/rendering/rendering_api.h"
#include "core/rendering/renderer.h"
#include "core/rendering/layers/layer.h"
#include "entities/rendering/texture_renderer.h"
#include "core/events/window_event.h"
#include "core/scenes/scene_layer.h"
#include "core/rendering/camera.h"

namespace engine {
	Engine* Engine::_instance;
	const TimeValue EngineMetrics::frame_check_interval = 1.0_t / 30.0_t;

	Engine::Engine(const EngineSpecification& specification)
		: _specs(specification) {
		_instance = this;

		AssetDatabase::load_database();

		_window = create_scope<Window>(specification.name);
		_window->set_event_callback(EN_BIND_EVENT_FUNC(Engine::on_event));
		_window->init();

		RenderingAPI::init();
		Renderer::init();

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);
		_viewport = create_scope<Viewport>(vidmode->width, vidmode->height);

#ifndef DISABLE_IMGUI
		_imgui_layer = new imgui::ImGuiLayer();
		push_overlay(_imgui_layer);
#endif
		push_layer(new SceneLayer());
	}

	Engine::~Engine() {
		Renderer::finalize();
	}

	void Engine::run() {
		RenderingAPI::set_clear_color(glm::vec4(0.07f, 0.13f, 0.17f, 1.0f));

		while (_running) {
			time_calculations();

			for (Layer* layer : _layer_stack)
				layer->on_update();

			if (!_paused) {
				Renderer::reset_statistics();

				_viewport->get_framebuffer().bind();
				RenderingAPI::clear();

				Renderer::begin_scene(Camera::get_scene_camera());

				for (Layer* layer : _layer_stack)
					layer->render();

				Renderer::end_scene();
				_viewport->get_framebuffer().unbind();

#ifndef DISABLE_IMGUI
				_imgui_layer->begin();

				for (Layer* layer : _layer_stack)
					layer->on_imgui_render();

				_imgui_layer->end();
#endif

				for (Layer* layer : _layer_stack)
					layer->post_render();

				_window->swap_buffers();
			}
			_window->poll_events();
		}
	}

	void Engine::on_event(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(EN_BIND_EVENT_FUNC(Engine::on_window_close));
		dispatcher.dispatch<KeyPressedEvent>(EN_BIND_EVENT_FUNC(Engine::on_key_pressed));

		for (auto layer = _layer_stack.rbegin(); layer != _layer_stack.rend(); layer++) {
			if (event.handled)
				break;
			(*layer)->on_event(event);
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

	void Engine::resize_viewport(unsigned int width, unsigned int height) {
		if (width == 0 || height == 0) {
			_paused = true;
		} else {
			_viewport->resize(width, height);
			_paused = false;
		}

		EngineResizeViewportEvent event(width, height);
		on_event(event);
	}

	bool Engine::on_window_close(WindowCloseEvent& event) {
		_running = false;
		return true;
	}

	bool Engine::on_key_pressed(KeyPressedEvent& event) {
		if (event.is_repeat())
			return false;
		if (event.get_code() == key::F11) {
			_window->set_fullscreen(!_window->get_fullscreen());
			return true;
		}
		return false;
	}

	void Engine::time_calculations() {
		TimeValue current_time = Time::get_time_since_startup();
		Time::set_delta_time(&_last_frame_time);
		TimeValue time_diff = current_time - _fps_previous_time;
		_frame_count++;
		_metrics.total_frame_count++;
		if (time_diff >= EngineMetrics::frame_check_interval) {
			_metrics.fps = _metrics.fps = 1.0_t / time_diff * _frame_count;
			_metrics.ms = _metrics.ms = time_diff / _frame_count * 1000.0_t;
			_fps_previous_time = current_time;
			_frame_count = 0;
		}
	}
}
