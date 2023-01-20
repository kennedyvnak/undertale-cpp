#include "enpch.h"
#include "vertex_array.h"
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace engine::buffers {
	VertexArray::VertexArray() {
		glGenVertexArrays(1, &_id);
	}

	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &_id);
	}

	void VertexArray::gen_new() {
		if (_id)
			glDeleteVertexArrays(1, &_id);
		glGenVertexArrays(1, &_id);
	}

	void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
		const auto& elements = layout.get_elements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), (const void*)(unsigned __int64(offset)));
			offset += element.count * VertexBufferElement::get_size_of_type(element.type);
		}
	}

	void VertexArray::bind() const {
		glBindVertexArray(_id);
	}

	void VertexArray::unbind() const {
		glBindVertexArray(0);
	}
}
