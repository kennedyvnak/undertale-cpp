#include "vertex_buffer_layout.h"

void VertexBufferLayout::push(unsigned int type, unsigned int count) {
	_elements.push_back({ type, count, GL_FALSE });
	_stride += count * VertexBufferElement::get_size_of_type(type);
}