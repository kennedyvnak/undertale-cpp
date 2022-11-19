#include "index_buffer.h"

#include "utility/open_gl_handler.h"

IndexBuffer::IndexBuffer()
    : _created(false), _id(0) { }

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indices) {
    set_buffer(indices);
}

IndexBuffer::~IndexBuffer() {
    destroy_buffer();
}

void IndexBuffer::set_buffer(const std::vector<unsigned int>& indices) {
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    if (_created)
        destroy_buffer();

    GL_CALL(glGenBuffers(1, &_id));
    bind();
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));
    _created = true;
    unbind();
}

void IndexBuffer::destroy_buffer() {
    if (!_created)
        return;

    GL_CALL(glDeleteBuffers(1, &_id));
    _created = false;
}

void IndexBuffer::bind() const {
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
}

void IndexBuffer::unbind() const {
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
