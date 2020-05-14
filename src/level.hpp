#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "mesh.hpp"

class Level {
	public:
		constexpr static unsigned int BLOCKS_PER_SEGMENT = 9;

		struct Block {
			glm::vec3 up;
			glm::vec3 center;
			float height;
		};

		struct Segment {
			Block blocks[BLOCKS_PER_SEGMENT];
		};

		Level(const char *filename);
		~Level();

		void render(const ShaderProgram &shaderProgram) {
			_mesh.render(shaderProgram);
		}

	private:
		std::vector<Segment> _segments;
		Mesh _mesh;
};

#endif
