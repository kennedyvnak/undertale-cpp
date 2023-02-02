#include "enpch.h"
#include "uniform_buffer.h"
#include <GL/glew.h>

namespace engine {
    UniformBuffer::UniformBuffer(unsigned int size, unsigned int binding) {
        glCreateBuffers(1, &_id);
        glNamedBufferData(_id, size, nullptr, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, _id);
    }

    UniformBuffer::~UniformBuffer() {
        glDeleteBuffers(1, &_id);
    }

    void UniformBuffer::set_data(const void* data, unsigned int size, unsigned int offset) {
        glNamedBufferSubData(_id, offset, size, data);
    }
}