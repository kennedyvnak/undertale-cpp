#include "enpch.h"
#include "viewport.h"
#include "engine.h"

namespace engine {
    Viewport::Viewport(int width, int height) {
        _framebuffer = create_scope<Framebuffer>(width, height);
        resize(width, height);
    }

    void Viewport::resize(int width, int height) {
        _framebuffer->resize(width, height);
        glViewport(0, 0, width, height);
        if (auto camera = Engine::get_instance()->get_camera())
            camera->set_aspect_ratio((float)width / (float)height);
    }
}