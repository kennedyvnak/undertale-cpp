#include "index_buffer.h"

#include "utility/open_gl_handler.h"

IndexBuffer::IndexBuffer()
	: _id(0) { }

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indices) {
	set_buffer(indices);
}

IndexBuffer::~IndexBuffer() {
	if (_id)
		GL_CALL(glDeleteBuffers(1, &_id));
}

void IndexBuffer::set_buffer(const std::vector<unsigned int>& indices) {
	ASSERT(sizeof(unsigned int) == sizeof(GLuint), "bytes lenght of unsigned int isn't equal to bytes lenght of GLuint.");

	if (_id)
		GL_CALL(glDeleteBuffers(1, &_id));

	GL_CALL(glGenBuffers(1, &_id));
	bind();
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));
	unbind();
}

void IndexBuffer::bind() const {
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
}

void IndexBuffer::unbind() const {
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
