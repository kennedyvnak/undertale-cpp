#include <memory>
#include <string>
#include <GLFW/glfw3.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "utility/open_gl_handler.h"
#include "core/rendering/window.h"
#include "core/rendering/vertex_buffer.h"
#include "core/rendering/index_buffer.h"
#include "core/rendering/vertex_array.h"
#include "core/rendering/vertex_buffer_layout.h"
#include "core/rendering/shader.h"
#include "core/rendering/material.h"
#include "core/rendering/mesh.h"
#include "core/rendering/texture.h"
#include "core/rendering/camera.h"
#include "core/components/transform.h"
#include "core/assets/asset_database.h"
#include "entities/rendering/texture_renderer.h"
#include "core/logging/logger.h"

int main(void) {
	Logger::initialize_logger();
	AssetDatabase::load_database();

	glfwSetErrorCallback(glfw_error_callback);

	std::shared_ptr<Window> window = std::make_shared<Window>("Undertale Clone in C++");
	if (window->init() == -1)
		return -1;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window->get_ptr(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

	if (glewInit() != GLEW_OK)
		LOG_ERROR("Glew initialization failed.");
	
	GL_CALL(glEnable(GL_BLEND));
	GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	GL_CALL(std::string gl_version = (char*)glGetString(GL_VERSION));
	GL_CALL(std::string gl_renderer = (char*)glGetString(GL_RENDERER));
	LOG_FORMAT("Initialize OpenGL | Version: {} | Renderer: {}", gl_version, gl_renderer);

	{
		std::shared_ptr<Camera> cam = std::make_shared<Camera>(0.0f, float(window->get_width()), 0.0f, float(window->get_height()), -1.0f, 1.0f);

		std::shared_ptr<Texture> texture = AssetDatabase::load_texture("res/textures/hearth.png");

		std::shared_ptr<TextureRenderer> tex_renderer = std::make_shared<TextureRenderer>(texture, Transform(glm::vec2(window->get_width() * 0.5f, window->get_height() * 0.5f), 0.0f, glm::vec2(100.0f)));

		while (!window->should_close()) {
			GL_CALL(glClearColor(0.07f, 0.13f, 0.17f, 1.0f));
			GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			{
				int width = window->get_width();
				int height = window->get_height();
				bool fullscreen = window->get_fullscreen();
				bool vsync = window->get_vsync();

				ImGui::Begin("Configs");
				ImGui::SliderInt("Width", &width, 640, 1366);
				ImGui::SliderInt("Heght", &height, 300, 768);
				ImGui::Checkbox("Fullscreen", &fullscreen);
				ImGui::Checkbox("V-sync", &vsync);
				ImGui::End();

				if (width != window->get_width()) {
					window->set_width(width);
				}
				if (height != window->get_height()) {
					window->set_height(height);
				}
				if (fullscreen != window->get_fullscreen()) {
					window->set_fullscreen(fullscreen);
				}
				if (vsync != window->get_vsync()) {
					window->set_vsync(vsync);
				}
			}

			{
				Transform& t = tex_renderer->get_transform();
				glm::vec2 translation = t.get_position();
				float rotation = t.get_rotation();
				glm::vec2 scale = t.get_scale();
				ImGui::Begin("Properties");
				ImGui::SliderFloat2("Translation", &translation.x, 0.0f, float(window->get_width()));
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

			window->swap_buffers();

			glfwPollEvents();
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}
