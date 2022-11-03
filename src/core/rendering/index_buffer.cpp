#include "index_buffer.h"

#include "utility/open_gl_handler.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) 
    : _count(count) {
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GL_CALL(glGenBuffers(1, &_id));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GL_CALL(glDeleteBuffers(1, &_id));
}

void IndexBuffer::bind() const {
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
}

void IndexBuffer::unbind() const {
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
