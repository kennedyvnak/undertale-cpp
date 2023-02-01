#include "enpch.h"
#include "vertex_array.h"
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace engine {
	static GLenum uniform_type_to_gl_base_type(UniformType uniform_type) {
		switch (uniform_type) {
		case UniformType::Float: return GL_FLOAT;
		case UniformType::Vec2: return GL_FLOAT;
		case UniformType::Vec3: return GL_FLOAT;
		case UniformType::Vec4: return GL_FLOAT;
		case UniformType::Mat4: return GL_FLOAT;
		case UniformType::Int: return GL_INT;
		}
		EN_ASSERT(false, "Unknow uniform type.");
		return 0;
	}

	VertexArray::VertexArray() {
		glGenVertexArrays(1, &_id);
	}

	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &_id);
	}

	void VertexArray::bind() const {
		glBindVertexArray(_id);
	}

	void VertexArray::unbind() const {
		glBindVertexArray(0);
	}

	void VertexArray::add_vertex_buffer(const Ref<VertexBuffer>& vertex_buffer) {
		glBindVertexArray(_id);
		vertex_buffer->bind();

		const auto& layout = vertex_buffer->get_layout();
		for (const auto& element : layout) {
			switch (element.type) {
			case UniformType::Float:
			case UniformType::Vec2:
			case UniformType::Vec3:
			case UniformType::Vec4:
			{
				glEnableVertexAttribArray(_vertex_buffer_index);
				glVertexAttribPointer(_vertex_buffer_index,
					element.get_component_count(),
					uniform_type_to_gl_base_type(element.type),
					element.normalized ? GL_TRUE : GL_FALSE,
					layout.get_stride(),
					(const void*)element.offset);
				_vertex_buffer_index++;
				break;
			}
			case UniformType::Int:
			{
				glEnableVertexAttribArray(_vertex_buffer_index);
				glVertexAttribIPointer(_vertex_buffer_index,
					element.get_component_count(),
					uniform_type_to_gl_base_type(element.type),
					layout.get_stride(),
					(const void*)element.offset);
				_vertex_buffer_index++;
				break;
			}
			case UniformType::Mat4:
			{
				unsigned char count = element.get_component_count();
				for (unsigned char i = 0; i < count; i++) {
					glEnableVertexAttribArray(_vertex_buffer_index);
					glVertexAttribPointer(_vertex_buffer_index,
						count,
						uniform_type_to_gl_base_type(element.type),
						element.normalized ? GL_TRUE : GL_FALSE,
						layout.get_stride(),
						(const void*)(element.offset + sizeof(float) * count * i));
					glVertexAttribDivisor(_vertex_buffer_index, 1);
					_vertex_buffer_index++;
				}
				break;
			}
			default:
				EN_ASSERT(false, "Unknow uniform type.");
			}
		}

		_vertex_buffers.push_back(vertex_buffer);
	}

	void VertexArray::set_index_buffer(const Ref<IndexBuffer>& index_buffer) {
		bind();
		index_buffer->bind();
		_index_buffer = index_buffer;
	}
}
