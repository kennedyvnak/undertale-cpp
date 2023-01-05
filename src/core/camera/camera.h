#pragma once

#include "engine.h"
#include "core/components/transform.h"
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
	Transform _transform;
	Matrix _projection, _view_projection;
	void recalculate_matrix();

public:
	Camera();
	Camera(float left, float right, float top, float bottom, float near, float far);

	void set_bounds(float left, float right, float top, float bottom, float near, float far);

	inline const Matrix get_projection() const& { return _projection; }
	void set_projection(Matrix value) { _projection = value; recalculate_matrix(); }

	inline const Matrix get_view_projection() const& { return _view_projection; }

	inline Transform& get_transform() { return _transform; }
	void set_position(Vector2 position);
	void set_rotation(float rotation);
	void set_scale(Vector2 scale);
};

