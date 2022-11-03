#pragma once

#include <GL/glew.h>
#include <vector>

#include "utility/open_gl_handler.h"

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int get_size_of_type(unsigned int type) {
		switch (type) {
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> _elements;
	unsigned int _stride;

public:
	VertexBufferLayout()
		: _stride(0) {}

	template<typename T>
	void push(unsigned int count) {
		//static_assert(false);
	}

	void push(unsigned int type, unsigned int count) {
		_elements.push_back({ type, count, GL_FALSE });
		_stride += count * VertexBufferElement::get_size_of_type(type);
	}
	
	inline const std::vector<VertexBufferElement> get_elements() const& { return _elements; }
	inline unsigned int get_stride() const { return _stride; }
};

