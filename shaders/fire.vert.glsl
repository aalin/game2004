#version 120

attribute vec3 aPosition;
attribute float aIndex;

uniform mat4 uMVPMatrix;
uniform float uTime;

varying vec4 vColor;

mat4 rotationY(float angle) {
  float ca = cos(angle);
  float sa = sin(angle);

  return mat4(
     ca, 0.0,  sa, 0.0,
    0.0, 1.0, 0.0, 0.0,
    -sa, 0.0,  ca, 0.0,
    0.0, 0.0, 0.0, 1.0
  );
}

float rand(vec2 co) {
  return fract(sin(dot(co.xy, vec2(12.9898, 78.223))) * 43758.5453);
}

vec3 color(float x) {
  float r = 1.0 + (sin((x + 0.0 / 3.0) * 3.14159)) * 0.5;
  float g = (sin((x + 1.0 / 3.0) * 3.14159));

  return vec3(r, r - (g * g) * 0.25, 0.0);
}

void main() {
  float rot = rand(vec2(floor(uTime * 10.0), aIndex)) * 3.14159;
  vec4 position = vec4(aPosition, 1.0) * rotationY(rot * 2);
	gl_Position = uMVPMatrix * position;

  vColor = vec4(color(uTime * 3.0 + aIndex / 2.0), 0.5);
}
