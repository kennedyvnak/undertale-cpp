#pragma once

#include <vector>

class IndexBuffer {
private:
	unsigned int _id;
	bool _created;

public:
	IndexBuffer();
	IndexBuffer(const std::vector<unsigned int>& indices);
	~IndexBuffer();

	void set_buffer(const std::vector<unsigned int>& indices);
	void destroy_buffer();
	inline const bool is_valid() const& { return _created; }

	void bind() const;
	void unbind() const;
};

