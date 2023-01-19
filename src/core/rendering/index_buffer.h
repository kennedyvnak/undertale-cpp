#pragma once

#include "enpch.h"

namespace engine::buffers {
	class IndexBuffer {
	private:
		unsigned int _id;

	public:
		IndexBuffer();
		IndexBuffer(const std::vector<unsigned int>& indices);
		~IndexBuffer();

		void set_buffer(const std::vector<unsigned int>& indices);

		void bind() const;
		void unbind() const;
	};
}