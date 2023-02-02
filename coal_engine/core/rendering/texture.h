#pragma once

#include <string>
#include "core/assets/asset.h"

namespace engine {
	class Texture: public Asset {
	private:
		unsigned int _id;
		unsigned char* _local_buffer;
		int _width, _height, _bpp;

	public:
		Texture();
		Texture(int width, int height);
		Texture(const std::string& path);
		~Texture();

		static Ref<Texture> GenFlatTexture(int width, int height, unsigned int color_bytes);

		void bind(unsigned int slot) const;
		void unbind() const;

		void resize(int width, int height);

		inline int get_width() const { return _width; }
		inline int get_height() const { return _height; }
		inline unsigned int get_id() const { return _id; }
	};
}
