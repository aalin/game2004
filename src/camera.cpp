#include "camera.hpp"
#include "utils.hpp"
#include <glm/ext.hpp>
#include <cmath>

Camera::Camera() :
	_position(0.0, 0.0, 0.0),
	_targetPosition(0.0, 0.0, 0.0),
	_lookAt(1.0, 1.0, 0.0),
	_targetLookAt(1.0, 1.0, 0.0),
	_up(0.0, 0.0, 1.0) {
}

void Camera::update(double dt) {
	_position = Utils::tween(_position, _targetPosition, 5.0, dt);
	_lookAt = Utils::tween(_lookAt, _targetLookAt, 5.0, dt);

	_matrix = glm::lookAt(
		_position,
		_lookAt,
		_up
	);
}


