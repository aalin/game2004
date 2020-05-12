#ifndef SHADER_SOURCE_HPP
#define SHADER_SOURCE_HPP

#include <string>

class ShaderSource {
	public:
		ShaderSource(std::string filename);
		~ShaderSource();

	private:
		std::string _filename;
		std::string _source;
};

#endif
