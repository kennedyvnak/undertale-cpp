#pragma once

#include <glm/glm.hpp>
#include "core/components/transform.h"

namespace engine {
	class Camera {
	public:
		Camera();
		Camera(float aspect_ratio);

		inline float get_near() const { return _near; }
		void set_near(float near) { _near = near; recalculate_projection(); }

		inline float get_far() const { return _far; }
		void set_far(float far) { _far = far; recalculate_projection(); }

		inline float get_aspect_ratio() const { return _aspect_ratio; }
		void set_aspect_ratio(float aspect_ratio) { _aspect_ratio = aspect_ratio; recalculate_projection(); }

		inline float get_size() const { return _size; }
		void set_size(float size) { _size = size; recalculate_projection(); }

		inline const glm::mat4 get_projection() const& { return _projection; }
		void set_projection(glm::mat4 value) { _projection = value; recalculate_matrix(); }

		inline const glm::mat4 get_view_projection() const& { return _view_projection; }

		inline Transform& get_transform() { return _transform; }
		void set_position(glm::vec2 position);
		void set_rotation(float rotation);
		void set_scale(glm::vec2 scale);
	private:
		float _near;
		float _far;
		float _aspect_ratio;
		float _size;

		Transform _transform;
		glm::mat4 _projection, _view_projection;
		void recalculate_matrix();
		void recalculate_projection();
	};
}
