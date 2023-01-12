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
#include "core/rendering/vertex_buffer.h"
#include "core/rendering/index_buffer.h"
#include "core/rendering/vertex_array.h"
#include "core/rendering/vertex_buffer_layout.h"
#include "core/rendering/shader.h"
#include "core/rendering/material.h"
#include "core/rendering/mesh.h"
#include "core/rendering/texture.h"
#include "core/camera/camera.h"
#include "core/components/transform.h"
#include "entities/rendering/texture_renderer.h"

int main(void) {
    int window_width = 16 * 64;
    int window_height = 9 * 64;
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(window_width, window_height, "Undertale", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    if (glewInit() != GLEW_OK)
        std::cout << "Error on glew initialization!" << std::endl;

    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    std::cout << "Initialize OpenGL " << glGetString(GL_VERSION) << "\n.\n." << std::endl;

    {
        std::shared_ptr<Camera> cam = std::make_shared<Camera>(0.0f, float(window_width), 0.0f, float(window_height), -1.0f, 1.0f);

        std::shared_ptr<Texture> texture = std::make_shared<Texture>("res/textures/hearth.png");

        std::shared_ptr<TextureRenderer> tex_renderer = std::make_shared<TextureRenderer>(texture, Transform(glm::vec2(window_width * 0.5f, window_height * 0.5f), 0.0f, glm::vec2(100.0f)));

        while (!glfwWindowShouldClose(window)) {
            GL_CALL(glClearColor(0.07f, 0.13f, 0.17f, 1.0f));
            GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                Transform& t = tex_renderer->get_transform();
                glm::vec2 translation = t.get_position();
                float rotation = t.get_rotation();
                glm::vec2 scale = t.get_scale();
                ImGui::Begin("Properties");
                ImGui::SliderFloat2("Translation", &translation.x, 0.0f, float(window_width));
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

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
