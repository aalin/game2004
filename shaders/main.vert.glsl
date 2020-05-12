#version 120

attribute vec3 aPosition;

uniform mat4 MVP;

void main() {
	gl_Position = MVP * vec4(aPosition, 1.0);
}
