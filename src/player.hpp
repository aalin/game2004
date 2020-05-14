#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "mesh.hpp"

class Player {
	public:
		Player();
		~Player();

		void reset() {
			_position = glm::vec3(0.0, 1.0, 0.01);
			_movement = glm::vec3(0.0, 0.0, 0.0);
			_velocity = glm::vec3(0.0, 0.0, 0.0);
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

		const glm::vec3& velocity() const {
			return _velocity;
		}

		float getFireStrength() const {
			return _fireStrength;
		}

		void moveX(float value) {
			_movement.x = value;
		}

		void moveY(float value) {
			_movement.y = value;
		}

		void update(double dt);

	private:
		Mesh _mesh;
		Mesh _fireMesh;
		glm::vec3 _position;
		glm::vec3 _velocity;
		glm::vec3 _movement;
		float _fireStrength;
};

#endif
