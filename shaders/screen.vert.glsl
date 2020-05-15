#version 120

attribute vec2 aPosition;
attribute vec2 aTexCoords;

varying vec2 vTexCoords;

void main() {
  gl_Position = vec4(aPosition, 0.0, 1.0);
  vTexCoords = aTexCoords;
}
