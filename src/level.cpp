#include "level.hpp"
#include "logger.hpp"
#include <string>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>

std::vector<Level::Segment> loadBlocks(const char *filename) {
	std::ifstream is(filename);

	std::vector<Level::Segment> segments;

	if (is.fail()) {
		Logger::error("Could not read", filename);
		throw "Could not read the file";
	}

	while (!is.eof()) {
		Level::Segment segment;
		is.read(&segment.blocks[0], 9);
		INFO("blocks", std::string(segment.blocks, 9));

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

int getSegmentValue(const std::vector<Level::Segment> &segments, int x, int y) {
	const int blockIndex = 9 - x - 1;

	if (blockIndex < 0 || blockIndex > 9) {
		return -1;
	}

	const int value = segments[y].blocks[blockIndex] - 48;

	if (value < 0 || value > 9) {
		return -1;
	}

	return value;
}

Level::Level(const char *filename) :
_mesh(Mesh::PrimitiveType::Triangles) {
	Logger::log("Constructing level");

	_segments = loadBlocks(filename);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> normals;

	for (unsigned int y = 0; y < _segments.size(); y++) {
		for (unsigned int x = 0; x < 9; x++) {
			const int value = getSegmentValue(_segments, x, y);

			if (value == -1) {
				continue;
			}

			const float height = 0.4;
			const float bottomHeight = 0.2;

			const float x0 = x - 4.5;
			const float x1 = x0 + 1;

			const float y0 = y;
			const float y1 = y + 1;

			const float z = value * height;

			addQuad(
				vertices,
				normals,
				glm::vec3({ x0, y0, z }),
				glm::vec3({ x1, y0, z }),
				glm::vec3({ x0, y1, z }),
				glm::vec3({ x1, y1, z })
			);

			const glm::vec3 c0 = colorAt(y0 / 10 + z / 20);
			const glm::vec3 c1 = colorAt(y1 / 10 + z / 20);

			addQuad(colors, c0, c0, c1, c1);

			// Left

			{
				const int sideValue = getSegmentValue(_segments, x - 1, y);

				if (sideValue < value) {
					const float z1 = z;
					const float z2 = sideValue < 0 ? -bottomHeight : sideValue * height;

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
				const int sideValue = getSegmentValue(_segments, x + 1, y);

				if (sideValue < value) {
					const float z1 = z;
					const float z2 = sideValue < 0 ? -bottomHeight : sideValue * height;

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

			// Front

			{
				const int sideValue = getSegmentValue(_segments, x, y - 1);

				if (sideValue < value) {
					const float z1 = z;
					const float z2 = sideValue < 0 ? -bottomHeight : sideValue * height;

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
		}
	}

	_mesh.addBuffer("aPosition", vertices);
	_mesh.addBuffer("aNormal", normals);
	_mesh.addBuffer("aColor", colors);
}

Level::~Level() {
	Logger::error("Destroying level");
}
