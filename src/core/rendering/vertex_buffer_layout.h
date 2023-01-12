#pragma once

#include <GL/glew.h>
#include <vector>
#include "core/logging/logger.h"

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
		ASSERT_FORMAT(false, "Type '{}' isn't supported.", type);
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

	void push(unsigned int type, unsigned int count);
	
	inline const std::vector<VertexBufferElement> get_elements() const& { return _elements; }
	inline unsigned int get_stride() const { return _stride; }
};

