#pragma once

#include "core/base.h"
#include <glm/glm.hpp>
#include "core/rendering/texture.h"
#include "core/rendering/material.h"
#include "core/rendering/mesh.h"
#include "core/rendering/camera.h"
#include "core/components/transform.h"

namespace engine {
	namespace entities {
		class TextureRenderer {
		private:
			Ref<Texture> _texture;
			Ref<Material> _material;
			Ref<Mesh> _mesh;
			Transform _transform;

			static Ref<Material> get_default_material();

		public:
			TextureRenderer();
			TextureRenderer(Ref<Texture> texture);
			TextureRenderer(Ref<Texture> texture, const Transform& _transform);
			TextureRenderer(Ref<Texture> texture, Ref<Material> material);
			TextureRenderer(Ref<Texture> texture, Ref<Material> material, const Transform& _transform);
			~TextureRenderer();

			void draw(Ref<Camera> camera);

			inline Ref<Texture> get_texture() const { return _texture; }
			inline Ref<Material> get_material() const { return _material; }
			inline Transform& get_transform()& { return _transform; }

			void set_position(glm::vec2 position);
			void set_scale(glm::vec2 scale);
			void set_rotation(float rotation);

			void set_texture(Ref<Texture> texture) { _texture = texture; }
			void set_material(Ref<Material> material) { _material = material; }
			void set_transform(const Transform& transform) { _transform = transform; }
		};
	}
}
