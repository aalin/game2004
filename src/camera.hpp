#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Camera {
	public:
		Camera();

		void move(glm::vec3 position) {
			_targetPosition = position;
		}

		const glm::vec3 & position() const {
			return _position;
		}

		void lookAt(glm::vec3 lookAt) {
			_targetLookAt = lookAt;
		}

		void update(double dt);

		const glm::mat4 & getMatrix() { return _matrix; }

	private:
		glm::vec3 _position;
		glm::vec3 _targetPosition;
		glm::vec3 _lookAt;
		glm::vec3 _targetLookAt;
		glm::vec3 _up;
		glm::mat4 _matrix;
};

#endif
