#include "enpch.h"
#include "index_buffer.h"
#include <GL/glew.h>

namespace engine::buffers {
	IndexBuffer::IndexBuffer()
		: _id(0) { }

	IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indices) {
		set_buffer(indices);
	}

	IndexBuffer::~IndexBuffer() {
		if (_id)
			glDeleteBuffers(1, &_id);
	}

	void IndexBuffer::set_buffer(const std::vector<unsigned int>& indices) {
		EN_ASSERT(sizeof(unsigned int) == sizeof(GLuint), "Bytes lenght of unsigned int isn't equal to bytes lenght of GLuint.");

		if (_id)
			glDeleteBuffers(1, &_id);

		glGenBuffers(1, &_id);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		unbind();
	}

	void IndexBuffer::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
	}

	void IndexBuffer::unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
