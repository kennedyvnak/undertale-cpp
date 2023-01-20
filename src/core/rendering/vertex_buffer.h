#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace engine {
	struct Vertex {
		glm::vec2 position;
		glm::vec2 uv;
	};

	namespace buffers {
		class VertexBuffer {
		private:
			unsigned int _id;

		public:
			VertexBuffer(std::vector<Vertex>& vertices);
			~VertexBuffer();

			void bind() const;
			void unbind() const;
		};
	}
}
