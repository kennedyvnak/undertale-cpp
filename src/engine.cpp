#include <GLFW/glfw3.h>
#include <gl/glew.h>

#include <iostream> 
#include <fstream>
#include <string>
#include <sstream>

#include "utility/open_gl_handler.h"
#include "core/rendering/vertex_buffer.h"
#include "core/rendering/index_buffer.h"

struct ShaderProgramSource {
    std::string vertex_source;
    std::string fragment_source;
};

static ShaderProgramSource parse_shader(const std::string& filepath) {
    std::ifstream stream(filepath);
    
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

static unsigned int compile_shader(unsigned int type, const std::string& source) {
    GL_CALL(unsigned int id = glCreateShader(type));

    const char* src = source.c_str();
    GL_CALL(glShaderSource(id, 1, &src, nullptr));
    GL_CALL(glCompileShader(id));

    int result;
    GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)_malloca(length * sizeof(char));
        GL_CALL(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader! " << std::endl;
        std::cout << message << std::endl;
        GL_CALL(glDeleteShader(id));
        return 0;
    }

    return id;
}

static unsigned int create_shader(const std::string& vert_shader_source, const std::string& frag_shader_source) {
    GL_CALL(unsigned int program = glCreateProgram());
    unsigned int vertex_shader = compile_shader(GL_VERTEX_SHADER, vert_shader_source);
    unsigned int fragment_shader = compile_shader(GL_FRAGMENT_SHADER, frag_shader_source);

    GL_CALL(glAttachShader(program, vertex_shader));
    GL_CALL(glAttachShader(program, fragment_shader));
    GL_CALL(glLinkProgram(program));
    GL_CALL(glValidateProgram(program));

    GL_CALL(glDeleteShader(vertex_shader));
    GL_CALL(glDeleteShader(fragment_shader));

    return program;
}

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

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    if (glewInit() != GLEW_OK)
        std::cout << "Error on glew initialization!" << std::endl;

    std::cout << "Initialize OpenGL " << glGetString(GL_VERSION) << "\n.\n." << std::endl;

    {
        float positions[8] = {
            -0.5f, -0.5f,
             0.5f,  -0.5f,
             0.5f, 0.5f,
             -0.5f, 0.5f,
        };

        unsigned int indices[6] = {
            0, 1, 2,
            2, 3, 0
        };

        unsigned int vao;
        GL_CALL(glGenVertexArrays(1, &vao));
        GL_CALL(glBindVertexArray(vao));

        VertexBuffer vb(positions, 8 * sizeof(float));

        GL_CALL(glEnableVertexAttribArray(0));
        GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

        IndexBuffer ib(indices, 6);

        ShaderProgramSource source = parse_shader("res/shaders/basic.shader");
        unsigned int shader = create_shader(source.vertex_source, source.fragment_source);
        GL_CALL(glUseProgram(shader));

        GL_CALL(int location = glGetUniformLocation(shader, "u_Color"));
        ASSERT(location != -1);

        GL_CALL(glBindVertexArray(0));
        GL_CALL(glUseProgram(0));
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        while (!glfwWindowShouldClose(window)) {
            GL_CALL(glClearColor(0.07f, 0.13f, 0.17f, 1.0f));
            GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

            float time = float(glfwGetTime());

            GL_CALL(glUseProgram(shader));
            GL_CALL(glUniform4f(location, 0.5f + sinf(time) * 0.5f, 0.5f + cosf(time) * 0.5f, 0.5f + sinf(time * 3.14) * 0.5f, 1.0f));

            GL_CALL(glBindVertexArray(vao));
            ib.bind();

            GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            glfwSwapBuffers(window);

            glfwPollEvents();
        }

        GL_CALL(glDeleteProgram(shader));
    }

    glfwTerminate();
    return 0;
}
