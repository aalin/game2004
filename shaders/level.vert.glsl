#version 120

attribute vec3 aPosition;
attribute vec3 aNormal;
attribute vec3 aColor;

uniform mat4 uMVPMatrix;
uniform mat4 uNormalMatrix;
uniform vec3 uLightPosition;
uniform vec3 uCameraPosition;

varying vec4 vColor;
varying vec4 vNormal;
varying vec3 vPosition;
varying vec3 vLighting;

vec4 rgb(float x) {
  vec4 c = vec4(
    sin((x + 0.0 / 3.0) * 3.14159),
    sin((x + 1.0 / 3.0) * 3.14159),
    sin((x + 2.0 / 3.0) * 3.14159),
    1.0
  );

  return c * c;
}

void main() {
  gl_Position = uMVPMatrix * vec4(aPosition, 1.0);

  vec3 ambientLight = vec3(0.6);
  vec3 directionalLightColor = vec3(0.2);

  vec3 directionalVector = normalize(uLightPosition - uCameraPosition);
  vNormal = uNormalMatrix * vec4(aNormal, 1.0);
  float directional = max(dot(vNormal.xyz, directionalVector), 0.0);

  vLighting = ambientLight + directionalLightColor * directional;

  vColor = vec4(aColor, 1.0);
  vPosition = gl_Position.xyz;
}
