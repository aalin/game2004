#version 120

attribute vec3 aPosition;
attribute vec3 aColor;

uniform mat4 MVP;

varying vec3 vColor;

void main() {
	gl_Position = MVP * vec4(aPosition, 1.0);
  vColor = aColor;
}
