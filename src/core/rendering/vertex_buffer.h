#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Vertex {
	glm::vec2 position;
	glm::vec2 uv;
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

