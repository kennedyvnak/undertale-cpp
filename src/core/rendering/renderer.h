#pragma once

#include "vertex_array.h"
#include "shader.h"
#include "index_buffer.h"

class Renderer {
public:
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void clear() const;
};

