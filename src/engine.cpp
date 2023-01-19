#include "enpch.h"
#include "engine.h"
#include "core/base.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "core/assets/asset_database.h"
#include "core/rendering/window.h"
#include "core/rendering/rendering_api.h"
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

		// IMGUI stuff
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(_window->get_ptr(), true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	Engine::~Engine() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Engine::run() {
		Ref<Camera> cam = create_ref<Camera>(0.0f, float(_window->get_width()), 0.0f, float(_window->get_height()), -1.0f, 1.0f);

		Ref<Texture> texture = AssetDatabase::load_texture("res/textures/hearth.png");

		Ref<entities::TextureRenderer> tex_renderer = create_ref<entities::TextureRenderer>(texture, Transform(glm::vec2(_window->get_width() * 0.5f, _window->get_height() * 0.5f), 0.0f, glm::vec2(100.0f)));

		rendering::RenderingAPI::set_clear_color(glm::vec4(0.07f, 0.13f, 0.17f, 1.0f));

		while (!_window->should_close()) {
			rendering::RenderingAPI::clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			{
				int width = _window->get_width();
				int height = _window->get_height();
				bool fullscreen = _window->get_fullscreen();
				bool vsync = _window->get_vsync();

				ImGui::Begin("Configs");
				ImGui::SliderInt("Width", &width, 640, 1366);
				ImGui::SliderInt("Heght", &height, 300, 768);
				ImGui::Checkbox("Fullscreen", &fullscreen);
				ImGui::Checkbox("V-Sync", &vsync);
				ImGui::End();

				if (width != _window->get_width()) {
					_window->set_width(width);
				}
				if (height != _window->get_height()) {
					_window->set_height(height);
				}
				if (fullscreen != _window->get_fullscreen()) {
					_window->set_fullscreen(fullscreen);
				}
				if (vsync != _window->get_vsync()) {
					_window->set_vsync(vsync);
				}
			}

			{
				Transform& t = tex_renderer->get_transform();
				glm::vec2 translation = t.get_position();
				float rotation = t.get_rotation();
				glm::vec2 scale = t.get_scale();
				ImGui::Begin("Properties");
				ImGui::SliderFloat2("Translation", &translation.x, 0.0f, float(_window->get_width()));
				ImGui::SliderFloat2("Scale", &scale.x, 0.0f, 300.0f);
				ImGui::SliderFloat("Rotation", &rotation, 0.0f, 360.0f);
				tex_renderer->set_position(translation);
				tex_renderer->set_rotation(rotation);
				tex_renderer->set_scale(scale);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();
			}

			float time = float(glfwGetTime());
			tex_renderer->get_material()->set_vector4("u_Color", glm::vec4(0.5f + sinf(time) * 0.5f, 0.5f + cosf(time) * 0.5f, 0.5f + sinf(time * 3.14f) * 0.5f, 1.0f));

			tex_renderer->draw(cam);

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
}
