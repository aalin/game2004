#version 120

attribute vec3 aPosition;
attribute float aIndex;

uniform mat4 uMVPMatrix;
uniform float uTime;
uniform float uPlayerVelocity;

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
  return mix(vec3(0.5, 0.1, 0.0), vec3(0.5, 0.5, 0.0), fract(x));
}

void main() {
  float rot = rand(vec2(floor(uTime * 5.0), aIndex));
  vec4 position = vec4(aPosition, 1.0);

  float scale = clamp(uPlayerVelocity, 0.001, 1.0);
  float xyscale = 0.8 + scale;

  position = position * vec4(xyscale, fract((uTime * aIndex) * scale), xyscale, 1.0);
  position = position * rotationY(rot * 3.14159 * 2);

	gl_Position = uMVPMatrix * position;

  float alpha = 0.2;

  if (aPosition.y < 0) {
    alpha = 0.0;
  }

  vColor = vec4(color(fract(uTime * 3.0 + aIndex / 2.0)), alpha);
}
