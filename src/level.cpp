#include "level.hpp"
#include "logger.hpp"
#include <string>
#include <fstream>
#include <cmath>
#include <limits>
#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>

int charToInt(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	}

	if (c >= 'A' && c <= 'Z') {
		return c - 'A';
	}

	if (c >= 'a' && c <= 'z') {
		return c - 'a';
	}

	return -1;
}

const float BLOCK_HEIGHT = 0.4;
const float BLOCK_LOWER_HEIGHT = -0.2;

float calculateHeight(char blockCode) {
	const float height = charToInt(blockCode) * BLOCK_HEIGHT;

	if (height < 0) {
		return BLOCK_LOWER_HEIGHT;
	}

	return height;
}

std::vector<Level::Segment> loadBlocks(const char *filename) {
	std::ifstream is(filename);

	std::vector<Level::Segment> segments;

	if (is.fail()) {
		Logger::error("Could not read", filename);
		throw "Could not read the file";
	}

	while (!is.eof()) {
		char rawHeights[Level::BLOCKS_PER_SEGMENT];
		is.read(&rawHeights[0], Level::BLOCKS_PER_SEGMENT);

		Level::Segment segment;
		INFO("blocks", std::string(rawHeights, Level::BLOCKS_PER_SEGMENT));

		for (unsigned int i = 0; i < Level::BLOCKS_PER_SEGMENT; i++) {
			segment.blocks[i].height = calculateHeight(rawHeights[i]);
		}

		segments.push_back(segment);

		char nl = is.get();
	}

	return segments;
}

glm::vec3 colorAt(float x) {
	const float pi = 3.14159;

    return glm::vec3(
        std::pow(std::sin((x + 0) * pi + 0 / 3.0 * pi), 2),
        std::pow(std::sin((x + 1) * pi + 1 / 3.0 * pi), 2),
        std::pow(std::sin((x + 2) * pi + 2 / 3.0 * pi), 2)
    );
}

void addQuad(std::vector<glm::vec3> &vertices, glm::vec3 v00, glm::vec3 v01, glm::vec3 v10, glm::vec3 v11) {
	vertices.push_back(v00);
	vertices.push_back(v01);
	vertices.push_back(v11);

	vertices.push_back(v00);
	vertices.push_back(v11);
	vertices.push_back(v10);
}

void addQuad(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, glm::vec3 v00, glm::vec3 v01, glm::vec3 v10, glm::vec3 v11) {
	addQuad(vertices, v00, v01, v10, v11);

	const glm::vec3 normal = glm::triangleNormal(v00, v01, v11);

	normals.push_back(normal);
	normals.push_back(normal);
	normals.push_back(normal);

	normals.push_back(normal);
	normals.push_back(normal);
	normals.push_back(normal);
}

float getSegmentHeight(const std::vector<Level::Segment> &segments, int x, int y) {
	if (x < 0 || x >= static_cast<int>(Level::BLOCKS_PER_SEGMENT)) {
		return BLOCK_LOWER_HEIGHT;
	}

	if (y < 0 || y >= static_cast<int>(segments.size())) {
		return BLOCK_LOWER_HEIGHT;
	}

	const int blockIndex = Level::BLOCKS_PER_SEGMENT - x - 1;

	return segments[y].blocks[blockIndex].height;
}

Level::Level(const char *filename) :
_mesh(Mesh::PrimitiveType::Triangles) {
	Logger::log("Constructing level");

	_segments = loadBlocks(filename);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> normals;

	for (unsigned int y = 0; y < _segments.size(); y++) {
		for (unsigned int x = 0; x < Level::BLOCKS_PER_SEGMENT; x++) {
			const float height = getSegmentHeight(_segments, x, y);

			if (height < 0) {
				continue;
			}

			const float x0 = x - 4.5;
			const float x1 = x0 + 1;

			const float y0 = y;
			const float y1 = y + 1;

			const float z = height;

			addQuad(
				vertices,
				normals,
				glm::vec3({ x0, y0, z }),
				glm::vec3({ x1, y0, z }),
				glm::vec3({ x0, y1, z }),
				glm::vec3({ x1, y1, z })
			);

			const glm::vec3 c0 = colorAt(y0 / 10);
			const glm::vec3 c1 = colorAt(y1 / 10);

			addQuad(colors, c0, c0, c1, c1);

			// Front

			{
				const float sideHeight = getSegmentHeight(_segments, x, y - 1);

				if (sideHeight < height) {
					const float z1 = z;
					const float z2 = sideHeight;

					addQuad(
						vertices,
						normals,
						glm::vec3({ x1, y0, z1 }),
						glm::vec3({ x0, y0, z1 }),
						glm::vec3({ x1, y0, z2 }),
						glm::vec3({ x0, y0, z2 })
					);

					addQuad(colors, c0, c0, c0, c0);
				}
			}

			// Left

			{
				const float sideHeight = getSegmentHeight(_segments, x - 1, y);

				if (sideHeight < height) {
					const float z1 = z;
					const float z2 = sideHeight;

					addQuad(
						vertices,
						normals,
						glm::vec3({ x0, y0, z1 }),
						glm::vec3({ x0, y1, z1 }),
						glm::vec3({ x0, y0, z2 }),
						glm::vec3({ x0, y1, z2 })
					);

					addQuad(colors, c0, c1, c0, c1);
				}
			}

			// Right

			{
				const float sideHeight = getSegmentHeight(_segments, x + 1, y);

				if (sideHeight < height) {
					const float z1 = z;
					const float z2 = sideHeight;

					addQuad(
						vertices,
						normals,
						glm::vec3({ x1, y1, z1 }),
						glm::vec3({ x1, y0, z1 }),
						glm::vec3({ x1, y1, z2 }),
						glm::vec3({ x1, y0, z2 })
					);

					addQuad(colors, c1, c0, c1, c0);
				}
			}
		}
	}

	_mesh.addBuffer("aPosition", vertices);
	_mesh.addBuffer("aNormal", normals);
	_mesh.addBuffer("aColor", colors);
}

float Level::heightAt(float x, float y) const {
	constexpr float halfWidth = Level::BLOCKS_PER_SEGMENT / 2.0;

	if (std::fabs(x) > halfWidth) {
		return -1;
	}

	if (y < 0.0 || y > _segments.size()) {
		return -1;
	}

	const int xi = static_cast<int>(halfWidth + x);
	const int yi = static_cast<int>(y);

	const Segment &segment = _segments[yi];

	return segment.blocks[Level::BLOCKS_PER_SEGMENT - xi - 1].height;
}

glm::vec3 Level::circleCollides(const glm::vec3 &position, float radius) const {
	// Almost everything here is incorrect.

	glm::vec2 position2d(position.x, position.y);

	const float currentHeight = heightAt(position.x, position.y);

	const int xi = static_cast<int>(position.x);
	const int yi = static_cast<int>(position.y);

	glm::vec3 result(0.0, 0.0, currentHeight);

	float minDiff = std::numeric_limits<float>::infinity();

	for (int x = 0; x < 3; x++) {
		const float x2 = x - 2.0;

		for (int y = 0; y < 3; y++) {
			if (y == 1 && x == 1) {
				continue;
			}

			const float y2 = x - 2.0;
			const float blockHeight = heightAt(position.x + x2, position.y + y2);

			if (position.z > blockHeight) {
				continue;
			}

			if (currentHeight > blockHeight) {
				continue;
			}

			glm::vec2 blockCenter(xi + x2, yi + y2);
			glm::vec2 difference = position2d - blockCenter;

			glm::vec2 direction = glm::normalize(difference);

			glm::vec2 clamped = glm::clamp(difference, -0.5f, 0.5f);
			glm::vec2 closest = blockCenter + clamped;

			difference = closest - position2d;

			float diffLength = glm::length(difference);

			if (diffLength < radius && diffLength < minDiff) {
				result.x = direction.x * radius;
				result.y = direction.y * radius;
				result.z = blockHeight;

				minDiff = diffLength;
			}
		}
	}

	return result;
}

Level::~Level() {
	Logger::error("Destroying level");
}
