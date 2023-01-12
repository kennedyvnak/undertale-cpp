#include "open_gl_handler.h"

void gl_clear_error() {
    while (glGetError() != GL_NO_ERROR);
}

bool gl_log_call(const char* function, const char* file, int line) {
    bool has_no_error = true;
    while (GLenum error = glGetError()) {
        LOG_ERROR_FORMAT("[OpenGL Error] ({}): {} {}:{}", error, function, file, line);
        has_no_error = false;
    }
    return has_no_error;
}