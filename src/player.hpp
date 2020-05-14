#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "mesh.hpp"

class Player {
	public:
		Player();
		~Player();

		void reset() {
			_position = glm::vec3(0.0, 1.0, 0.01);
			_speed = glm::vec3(0.0, 0.0, 0.0);
		}

		void render(const ShaderProgram& shaderProgram) {
			_mesh.render(shaderProgram);
		}

		void renderFire(const ShaderProgram& shaderProgram) {
			_fireMesh.render(shaderProgram);
		}

		const glm::vec3& position() const {
			return _position;
		}

		void moveX(float value) {
			_position.x += value;
		}

		void moveY(float value) {
			_position.y += value;
		}

	private:
		Mesh _mesh;
		Mesh _fireMesh;
		glm::vec3 _position;
		glm::vec3 _speed;
};

#endif
