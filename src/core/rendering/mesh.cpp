#include "mesh.h"
#include "shader.h"
#include "material.h"
#include "core/components/transform.h"

std::vector<Vertex> Mesh::quad_vertices = {
	{ Vector2(-0.5f, -0.5f), Vector2(0.0f, 0.0f) },
	{ Vector2( 0.5f, -0.5f), Vector2(1.0f, 0.0f) },
	{ Vector2( 0.5f,  0.5f), Vector2(1.0f, 1.0f) },
	{ Vector2(-0.5f,  0.5f), Vector2(0.0f, 1.0f) }
};

std::vector<unsigned int> Mesh::quad_indices = {
	0, 1, 2,
	2, 3, 0
};

Mesh::Mesh() {
	set_vertices(quad_vertices);
	set_indices(quad_indices);
	rebuild_mesh();
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int> indices) {
	set_vertices(vertices);
	set_indices(indices);
	rebuild_mesh();
}

void Mesh::draw(std::shared_ptr<Material> mat) const {
	mat->bind();
	_va.bind();
	_ib.bind();

	GL_CALL(glDrawElements(GL_TRIANGLES, GLsizei(indices.size()), GL_UNSIGNED_INT, nullptr));
	mat->unbind();
}

void Mesh::set_vertices(const std::vector<Vertex>& vertices) {
	Mesh::vertices = vertices;
}

void Mesh::set_indices(const std::vector<unsigned int>& indices) {
	Mesh::indices = indices;
}

void Mesh::rebuild_mesh() {
	_va.gen_new();
	_va.bind();
	VertexBuffer vb(vertices);
	vb.bind();
	_ib.set_buffer(indices);

	VertexBufferLayout layout;
	layout.push(GL_FLOAT, 2);
	layout.push(GL_FLOAT, 2);
	_va.add_buffer(vb, layout);

	_va.unbind();
	vb.unbind();
	_ib.unbind();
}

std::shared_ptr<Mesh> Mesh::make_quad_mesh() {
	return std::make_shared<Mesh>();
}
