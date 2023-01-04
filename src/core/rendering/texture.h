#pragma once

#include "engine.h"
#include "renderer.h"

class Texture {
private:
	unsigned int _id;
	String _filepath;
	unsigned char* _local_buffer;
	int _width, _height, _bpp;

public:
	Texture(const String& path);
	~Texture();

	void bind(unsigned int slot) const;
	void unbind() const;

	inline int get_width() const { return _width; }
	inline int get_height() const { return _height; }
};

