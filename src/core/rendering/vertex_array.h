#pragma once

#include <glm/glm.hpp>
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray {
private:
	unsigned int _id;

public:
	VertexArray();
	~VertexArray();

	void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	
	void bind() const;
	void unbind() const;
};

