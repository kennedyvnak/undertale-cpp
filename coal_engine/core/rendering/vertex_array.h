#pragma once

#include <memory>
#include "buffers.h"

namespace engine {
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void bind() const;
		void unbind() const;

		void add_vertex_buffer(const Ref<VertexBuffer>& vertex_buffer);
		Ref<IndexBuffer> get_index_buffer() const { return _index_buffer; }
		void set_index_buffer(const Ref<IndexBuffer>& index_buffer);

	private:
		unsigned int _id;
		unsigned int _vertex_buffer_index = 0;
		std::vector<Ref<VertexBuffer>> _vertex_buffers;
		Ref<IndexBuffer> _index_buffer;
	};
}
