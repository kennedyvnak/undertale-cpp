#pragma once 

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "core/base.h"

namespace engine {
    class Texture;

    class Framebuffer {
    public:
        Framebuffer(int width, int height);
        ~Framebuffer();

        void bind() const;
        void unbind() const;

        inline unsigned int get_frame_buffer_id() const { return _id; }
        Texture& get_texture() const { return *_texture; }
    private:
        unsigned int _id;
        Scope<Texture> _texture = nullptr;
    };
}