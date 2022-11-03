#include <GLFW/glfw3.h>
#include <gl/glew.h>

#include "utility/open_gl_handler.h"
#include "core/rendering/vertex_buffer.h"
#include "core/rendering/index_buffer.h"
#include "core/rendering/vertex_array.h"
#include "core/rendering/vertex_buffer_layout.h"
#include "core/rendering/shader.h"
#include "core/rendering/renderer.h"
#include "core/rendering/texture.h"

int main(void) {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(16*64, 9*64, "Undertale", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error on glew initialization!" << std::endl;

    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    std::cout << "Initialize OpenGL " << glGetString(GL_VERSION) << "\n.\n." << std::endl;

    {
        float positions[] = {
             -0.5f, -0.5f, 0.0f, 0.0f,
              0.5f, -0.5f, 1.0f, 0.0f,
              0.5f,  0.5f, 1.0f, 1.0f,
             -0.5f,  0.5f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        unsigned int vao;
        GL_CALL(glGenVertexArrays(1, &vao));
        GL_CALL(glBindVertexArray(vao));

        VertexArray va;
        VertexBuffer vb(positions, 16 * sizeof(float));
        VertexBufferLayout layout;
        layout.push(GL_FLOAT, 2);
        layout.push(GL_FLOAT, 2);
        va.add_buffer(vb, layout);

        IndexBuffer ib(indices, 6);

        Shader shader("res/shaders/basic.shader");
        shader.bind();

        Texture texture("res/textures/hearth.png");
        texture.bind(0);
        shader.set_uniform1i("u_Texture", 0);

        va.unbind();
        vb.unbind();
        ib.unbind();
        shader.unbind();
        texture.unbind();

        Renderer renderer;

        while (!glfwWindowShouldClose(window)) {
            renderer.clear();

            shader.bind();
            texture.bind(0);
            float time = float(glfwGetTime());
            shader.set_uniform4f("u_Color", 0.5f + sinf(time) * 0.5f, 0.5f + cosf(time) * 0.5f, 0.5f + sinf(time * 3.14f) * 0.5f, 1.0f);

            renderer.draw(va, ib, shader);
            
            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
