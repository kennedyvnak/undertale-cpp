#include "texture.h"

#include <stb_image.h>

Texture::Texture(const String& path)
	: _id(0), _filepath(path), _local_buffer(nullptr), _width(0), _height(0), _bpp(0) {
	stbi_set_flip_vertically_on_load(1);
	_local_buffer = stbi_load(path.c_str(), &_width, &_height, &_bpp, 0);
	
	GL_CALL(glGenTextures(1, &_id));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, _id));

	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _local_buffer));
	GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));

	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

	if (_local_buffer)
		stbi_image_free(_local_buffer);
}

Texture::~Texture() {
	GL_CALL(glDeleteTextures(1, &_id));
}

void Texture::bind(unsigned int slot) const {
	GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, _id));
}

void Texture::unbind() const {
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}
