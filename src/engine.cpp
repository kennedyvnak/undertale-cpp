#include <GLFW/glfw3.h>
#include <gl/glew.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define ASSERT(x) if (!(x)) __debugbreak();
#define DEBUG_OPEN_GL

#ifdef DEBUG_OPEN_GL
    #define GL_CALL(x) gl_clear_error(); x; ASSERT(gl_log_call(#x, __FILE__, __LINE__))
#else 
    #define GL_CALL(x) x
#endif

static void gl_clear_error() {
    while (glGetError() != GL_NO_ERROR);
}

static bool gl_log_call(const char* function, const char* file, int line) {
    bool has_no_error = true;
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        has_no_error = false;
    }
    return has_no_error;
}

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

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(16*64, 9*64, "Undertale", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error on glew initialization!" << std::endl;

    std::cout << "Initialize OpenGL " << glGetString(GL_VERSION) << "\n.\n." << std::endl;

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

    unsigned int buffer;
    GL_CALL(glGenBuffers(1, &buffer));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW));

    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));
    
    unsigned int ibo;
    GL_CALL(glGenBuffers(1, &ibo));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

    ShaderProgramSource source = parse_shader("res/shaders/basic.shader");
    unsigned int shader = create_shader(source.vertex_source, source.fragment_source);
    GL_CALL(glUseProgram(shader));

    while (!glfwWindowShouldClose(window)) {
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

        GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    GL_CALL(glDeleteProgram(shader));

    glfwTerminate();
    return 0;
}