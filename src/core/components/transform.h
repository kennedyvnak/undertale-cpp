#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Transform {
private:
	vec2 _position;
	float _rotation;
	vec2 _scale;
	mat4 _matrix;

	void recalculate_matrix();

public:
	Transform();
	Transform(vec2 position, float rotation, vec2 scale);

	void set_prs(vec2 position, float rotation, vec2 scale);

	inline const vec2 get_position() const& { return _position; }
	void set_position(vec2 position) { _position = position; recalculate_matrix(); }

	inline const float get_rotation() const& { return _rotation; }
	void set_rotation(float rotation) { _rotation = rotation; recalculate_matrix(); }

	inline const vec2 get_scale() const& { return _scale; }
	void set_scale(vec2 scale) { _scale = scale; recalculate_matrix(); }

	inline const mat4 get_matrix() const& { return _matrix; }
};

