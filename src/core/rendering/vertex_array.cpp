#include "vertex_array.h"
#include "platform/opengl/opengl_error_handler.h"

namespace engine::buffers {
	VertexArray::VertexArray() {
		GL_CALL(glGenVertexArrays(1, &_id));
	}

	VertexArray::~VertexArray() {
		GL_CALL(glDeleteVertexArrays(1, &_id));
	}

	void VertexArray::gen_new() {
		if (_id)
			GL_CALL(glDeleteVertexArrays(1, &_id));
		GL_CALL(glGenVertexArrays(1, &_id));
	}

	void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
		const auto& elements = layout.get_elements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& element = elements[i];
			GL_CALL(glEnableVertexAttribArray(i));
			GL_CALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), (const void*)(unsigned __int64(offset))));
			offset += element.count * VertexBufferElement::get_size_of_type(element.type);
		}
	}

	void VertexArray::bind() const {
		GL_CALL(glBindVertexArray(_id));
	}

	void VertexArray::unbind() const {
		GL_CALL(glBindVertexArray(0));
	}
}