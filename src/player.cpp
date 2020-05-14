#include "player.hpp"

Player::Player() :
_mesh(Mesh::PrimitiveType::Triangles) {
	reset();

	const float w = 0.5;

	_mesh.addBuffer("aPosition", std::vector<glm::vec3>({
		glm::vec3(-w, 0, 0.0),
		glm::vec3( w, 0, 0.0),
		glm::vec3( 0, w, 0.0)
	}));

	_mesh.addBuffer("aNormal", std::vector<glm::vec3>({
		glm::vec3(0.0, 0.0, 1.0),
		glm::vec3(0.0, 0.0, 1.0),
		glm::vec3(0.0, 0.0, 1.0),
	}));

	_mesh.addBuffer("aColor", std::vector<glm::vec3>({
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(1.0, 1.0, 1.0),
	}));
}

Player::~Player() {
}
