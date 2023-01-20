#include "enpch.h"
#include "rendering_api.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace engine::rendering {
    RenderingAPI* RenderingAPI::_current_api;

    void opengl_message_callback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam)
    {
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:         LOG_ERROR_FORMAT("[OpenGL]: {}", message); return;
        case GL_DEBUG_SEVERITY_MEDIUM:       LOG_ERROR_FORMAT("[OpenGL]: {}", message); return;
        case GL_DEBUG_SEVERITY_LOW:          LOG_WARNING_FORMAT("[OpenGL]: {}", message); return;
        case GL_DEBUG_SEVERITY_NOTIFICATION: LOG_FORMAT("[OpenGL]: {}", message); return;
        }

        ASSERT(false, "Unknown severity level!");
    }

    void glfw_error_callback(int error_code, const char* description) {
        LOG_ERROR_FORMAT("[GLFW Error] ({}): {}.", error_code, description);
        __debugbreak();
    }

    void RenderingAPI::init() {
        ASSERT(glewInit() == GLEW_OK, "Glew initialization failed.");

        _current_api = new RenderingAPI();

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(opengl_message_callback, nullptr);
        glfwSetErrorCallback(glfw_error_callback);

        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        LOG_FORMAT("Initialize OpenGL | Version: {} | Renderer: {}", (char*)glGetString(GL_VERSION), (char*)glGetString(GL_RENDERER));
    }

    void RenderingAPI::iset_clear_color(glm::vec4 color) {
        _clear_color = color;
    }

    void RenderingAPI::iclear() {
        glClearColor(_clear_color.r, _clear_color.g, _clear_color.b, _clear_color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
