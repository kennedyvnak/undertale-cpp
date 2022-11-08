#include "mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
	Mesh::vertices = vertices;
	Mesh::indices = indices;

	_va.bind();
	VertexBuffer vb(vertices);
	_ib.set_buffer(indices);

	VertexBufferLayout layout;
	layout.push(GL_FLOAT, 2);
	layout.push(GL_FLOAT, 2);
	_va.add_buffer(vb, layout);
	
	_va.unbind();
	vb.unbind();
	_ib.unbind();
}

void Mesh::draw(const Material& mat) const {
	mat.bind();
	_va.bind();
	_ib.bind();

	GL_CALL(glDrawElements(GL_TRIANGLES, GLsizei(indices.size()), GL_UNSIGNED_INT, nullptr));
}
