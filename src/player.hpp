#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "mesh.hpp"
#include "level.hpp"

class Player {
	public:
		Player();
		~Player();

		void reset() {
			_xRotation = 0.0;
			_position = glm::vec3(0.0, 1.0, 0.1);
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

		float getXRotation() const {
			return _xRotation;
		}

		void moveX(float value) {
			_movement.x = value;
		}

		void moveY(float value) {
			_movement.y = value;
		}

		void jump();

		void update(double dt, const Level &level);

	private:
		Mesh _mesh;
		Mesh _fireMesh;
		glm::vec3 _position;
		glm::vec3 _velocity;
		glm::vec3 _movement;
		float _xRotation;
		float _fireStrength;
};

#endif
