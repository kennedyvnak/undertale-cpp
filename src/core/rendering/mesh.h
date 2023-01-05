#pragma once

#include <memory>
#include "vertex_array.h"
#include "index_buffer.h"
#include "core/components/transform.h"

class Material;

class Mesh {
private:
	VertexArray _va;
	IndexBuffer _ib;
	Transform _transform;

public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

	void draw(std::shared_ptr<Material> mat) const;

	inline const VertexArray get_va() const& { return _va; }
	void set_va(const VertexArray& va) { _va = va; }

	inline const IndexBuffer get_ib() const& { return _ib; }
	void set_ib(const IndexBuffer& ib) { _ib = ib; }
};

