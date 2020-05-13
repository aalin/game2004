#include "level.hpp"
#include "logger.hpp"
#include <string>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>

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


Level::Level(const char *filename) :
_mesh(Mesh::PrimitiveType::Triangles) {
	Logger::log("Constructing level");

	_segments = loadBlocks(filename);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;

	unsigned int y = 0;

	for (const auto &segment : _segments) {
		for (int x = 0; x < 9; x++) {
			if (segment.blocks[8 - x] != 'x') {
				continue;
			}

			const float x0 = x - 4.5;
			const float x1 = x0 + 1;

			const float y0 = y;
			const float y1 = y + 1;

			vertices.push_back({ x0, y0, 0.0 });
			vertices.push_back({ x1, y0, 0.0 });
			vertices.push_back({ x1, y1, 0.0 });

			vertices.push_back({ x0, y0, 0.0 });
			vertices.push_back({ x1, y1, 0.0 });
			vertices.push_back({ x0, y1, 0.0 });

			const glm::vec3 c0 = colorAt(y0 / 100);
			const glm::vec3 c1 = colorAt(y1 / 100);

			colors.push_back(c0);
			colors.push_back(c0);
			colors.push_back(c1);

			colors.push_back(c0);
			colors.push_back(c1);
			colors.push_back(c1);
		}

		y++;
	}

	_mesh.addBuffer("aPosition", vertices);
	_mesh.addBuffer("aColor", colors);
}

Level::~Level() {
	Logger::error("Destroying level");
}
