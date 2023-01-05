#include "engine.h"

#include <memory>
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
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    if (glewInit() != GLEW_OK)
        std::cout << "Error on glew initialization!" << std::endl;

    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    std::cout << "Initialize OpenGL " << glGetString(GL_VERSION) << "\n.\n." << std::endl;

    {
        Vertex positions[] = {
            Vector2(-0.5f, -0.5f),   Vector2(0.0f, 0.0f),
            Vector2( 0.5f, -0.5f),   Vector2(1.0f, 0.0f),
            Vector2( 0.5f,  0.5f),   Vector2(1.0f, 1.0f),
            Vector2(-0.5f,  0.5f),   Vector2(0.0f, 1.0f)
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        std::shared_ptr<Camera> cam = std::make_shared<Camera>(0.0f, float(window_width), 0.0f, float(window_height), -1.0f, 1.0f);
        
        std::shared_ptr<Shader> shader = std::make_shared<Shader>("res/shaders/basic.shader");

        std::shared_ptr<Material> mat = std::make_shared<Material>(shader);

        std::vector<Vertex> pos(positions, positions + sizeof(positions) / sizeof(Vertex));
        std::vector<unsigned int> ind(indices, indices + sizeof(indices) / sizeof(unsigned int));
        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(pos, ind);

        std::shared_ptr<Texture> texture = std::make_shared<Texture>("res/textures/hearth.png");

        mat->set_texture("u_Texture", texture);

        Transform transform = Transform(Vector2(0.0f), 0.0f, Vector2(200.0f));

        while (!glfwWindowShouldClose(window)) {
            GL_CALL(glClearColor(0.07f, 0.13f, 0.17f, 1.0f));
            GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                Vector2 translation = transform.get_position();
                float rotation = transform.get_rotation();
                Vector2 scale = transform.get_scale();
                ImGui::Begin("Properties");
                ImGui::SliderFloat2("Translation", &translation.x, 0.0f, float(window_width));
                ImGui::SliderFloat2("Scale", &scale.x, 0.0f, 300.0f);
                ImGui::SliderFloat("Rotation", &rotation, 0.0f, 360.0f);
                transform.set_position(translation);
                transform.set_rotation(rotation);
                transform.set_scale(scale);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            float time = float(glfwGetTime());
            mat->set_vector4("u_Color", Vector4(0.5f + sinf(time) * 0.5f, 0.5f + cosf(time) * 0.5f, 0.5f + sinf(time * 3.14f) * 0.5f, 1.0f));

            Matrix mvp = cam->get_view_projection() * transform.get_matrix();
            mat->set_matrix("u_MVP", mvp);

            mesh->draw(mat);

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
