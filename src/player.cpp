#include "player.hpp"
#include <glm/gtx/normal.hpp>

struct Triangle {
	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;

	glm::vec3 normal() const {
		return glm::triangleNormal(a, b, c);
	}

	Triangle flipX() const {
		const glm::vec3 mul(-1.0, 1.0, 1.0);

		return {
			b * mul,
			a * mul,
			c * mul
		};
	}
};

const float h = 4.0;

const Triangle RIGHT_TRIANGLES[] = {
  {{0, 28, 0}, {0, 11, h}, {4, 15, 0}},
  {{4, 15, 0}, {0, 11, h}, {8, 10, 0}},
  {{4, 0, 0}, {8, 10, 0}, {0, 11, h}},
  {{4, 0, 0}, {0, 11, h}, {2, 0, h / 2}},
  {{0, 11, h}, {0, 0, 0}, {2, 0, h / 2}},
  {{0, 11, 0}, {2, 0, -h / 2}, {0, 0, 0}},
  // Backside
  {{2, 0, h / 2}, {0, 0, 0}, {4, 0, 0}},
  {{0, 0, 0}, {2, 0, -h / 2}, {4, 0, 0}},
  // Wings
  {{8, 20, 0}, {6, 0, 0}, {7, 0, 0.5}},
  {{8, 20, 0}, {7, 0, 0.5}, {10, 0, 0}},
  {{10, 0, 0}, {7, 0, 0.5}, {6, 0, 0}},
  {{6, 0, 0}, {8, 20, 0}, {7, 0, -0.5}},
  {{7, 0, -0.5}, {8, 20, 0}, {10, 0, 0}},
  {{6, 0, 0}, {7, 0, -0.5}, {10, 0, 0}}
};

template<typename T>
void pushThrice(std::vector<T> &vector, T value) {
	vector.push_back(value);
	vector.push_back(value);
	vector.push_back(value);
}

void buildModel(Mesh &mesh) {
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colors;

	const float scale = 0.03;

	const glm::vec3 color(0.5, 0.5, 0.8);

	const unsigned int count = sizeof(RIGHT_TRIANGLES) / sizeof(Triangle);

	for (unsigned int i = 0; i <= count; i++) {
		const Triangle &right = RIGHT_TRIANGLES[i];

		// Right side

		positions.push_back(right.a * scale);
		positions.push_back(right.b * scale);
		positions.push_back(right.c * scale);

		pushThrice(normals, right.normal());
		pushThrice(colors, color);

		// Left side

		const Triangle left = right.flipX();

		positions.push_back(left.a * scale);
		positions.push_back(left.b * scale);
		positions.push_back(left.c * scale);

		pushThrice(normals, left.normal());
		pushThrice(colors, color);
	}

	mesh.addBuffer("aPosition", positions);
	mesh.addBuffer("aNormal", normals);
	mesh.addBuffer("aColor", colors);
}

void buildFireModel(Mesh &mesh) {
	std::vector<glm::vec3> positions;
	std::vector<float> indexes;

	for (int i = 0; i < 15; i++) {
		const float w = 0.2;
		const float l = 1.0;

		positions.push_back(glm::vec3( 0.0, 0.0, 0.0));
		positions.push_back(glm::vec3(  -w,  -l,  -w));
		positions.push_back(glm::vec3(   w,  -l,  -w));

		pushThrice(indexes, static_cast<float>(i));

		positions.push_back(glm::vec3( 0.0, 0.0, 0.0));
		positions.push_back(glm::vec3(   w,  -l,  -w));
		positions.push_back(glm::vec3( 0.0,  -l,   w));

		pushThrice(indexes, static_cast<float>(i));

		positions.push_back(glm::vec3( 0.0, 0.0, 0.0));
		positions.push_back(glm::vec3( 0.0,  -l,   w));
		positions.push_back(glm::vec3(  -w,  -l,  -w));

		pushThrice(indexes, static_cast<float>(i));
	}

	mesh.addBuffer("aPosition", positions);
	mesh.addBuffer("aIndex", indexes);
}

Player::Player() :
_mesh(Mesh::PrimitiveType::Triangles),
_fireMesh(Mesh::PrimitiveType::Triangles) {
	reset();

	buildModel(_mesh);
	buildFireModel(_fireMesh);
}

Player::~Player() {
}
