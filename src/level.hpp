#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "mesh.hpp"

class Level {
	public:
		struct Segment {
			char blocks[9];
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
