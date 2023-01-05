#pragma once

#include "engine.h"
#include "core/components/transform.h"
#include <memory>

class Texture;
class Material;
class Mesh;
class Camera;

class TextureRenderer {
private:
	std::shared_ptr<Texture> _texture;
	std::shared_ptr<Material> _material;
	std::shared_ptr<Mesh> _mesh;
	Transform _transform;

	static std::shared_ptr<Material> get_default_material();

public:
	TextureRenderer();
	TextureRenderer(std::shared_ptr<Texture> texture);
	TextureRenderer(std::shared_ptr<Texture> texture, const Transform& _transform);
	TextureRenderer(std::shared_ptr<Texture> texture, std::shared_ptr<Material> material);
	TextureRenderer(std::shared_ptr<Texture> texture, std::shared_ptr<Material> material, const Transform& _transform);
	~TextureRenderer();

	void draw(std::shared_ptr<Camera> camera);

	inline std::shared_ptr<Texture> get_texture() const { return _texture; }
	inline std::shared_ptr<Material> get_material() const { return _material; }
	inline Transform& get_transform() & { return _transform; }

	void set_position(Vector2 position);
	void set_scale(Vector2 scale);
	void set_rotation(float rotation);

	void set_texture(std::shared_ptr<Texture> texture) { _texture = texture; }
	void set_material(std::shared_ptr<Material> material) { _material = material; }
	void set_transform(const Transform& transform) { _transform = transform; }
};