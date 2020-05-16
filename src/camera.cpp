#include "camera.hpp"
#include <glm/ext.hpp>
#include <cmath>
#include "logger.hpp"

Camera::Camera() :
	_position(0.0, 0.0, 0.0),
	_targetPosition(0.0, 0.0, 0.0),
	_lookAt(1.0, 1.0, 0.0),
	_targetLookAt(1.0, 1.0, 0.0),
	_up(0.0, 0.0, 1.0) {
}

constexpr float TWEEN_THRESHOLD = 0.0001;

glm::vec3 lerp(glm::vec3 x, glm::vec3 y, float t) {
	return x * (1.0f - t) + y * t;
}

glm::vec3 tween(const glm::vec3 &from, const glm::vec3 &to, float speed, double dt) {
	if (std::fabs(glm::length(from - to)) < TWEEN_THRESHOLD) {
		INFO("Camera is already there");
		return to;
	}

	return lerp(from, to, std::fmin(dt * speed, 1.0));
}

void Camera::update(double dt) {
	_position = tween(_position, _targetPosition, 5.0, dt);
	_lookAt = tween(_lookAt, _targetLookAt, 5.0, dt);

	_matrix = glm::lookAt(
		_position,
		_lookAt,
		_up
	);
}


