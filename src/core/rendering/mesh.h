#pragma once

#include "enpch.h"
#include "core/base.h"
#include "core/components/transform.h"
#include "vertex_array.h"
#include "index_buffer.h"

namespace engine {
	using namespace buffers;
	class Material;

	class Mesh {
	private:
		VertexArray _va;
		IndexBuffer _ib;
		Transform _transform;

		static std::vector<Vertex> quad_vertices;
		static std::vector<unsigned int> quad_indices;

	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		Mesh();
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int> indices);

		void draw(Ref<Material> mat) const;

		void set_vertices(const std::vector<Vertex>& vertices);
		void set_indices(const std::vector<unsigned int>& indices);

		void rebuild_mesh();

		static Ref<Mesh> make_quad_mesh();
	};
}
