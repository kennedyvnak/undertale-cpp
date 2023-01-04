#pragma once

#include "engine.h"
#include <vector>

struct Vertex {
	Vector2 position;
	Vector2 uv;
};

class VertexBuffer {
private:
	unsigned int _id;

public:
	VertexBuffer(std::vector<Vertex>& vertices);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
};

