#version 120

uniform vec3 uLightPosition;

varying vec4 vColor;
varying vec4 vNormal;
varying vec3 vLighting;
varying vec3 vPosition;

float cutoffMin = 0.01;
float cutoffMax = 0.10;

float fogFactor(float fogMin, float fogMax, float fogDensity) {
  float dist = gl_FragCoord.z / gl_FragCoord.w;

  if (dist >= fogMax) {
    return 1.0;
  }

  if (dist <= fogMin) {
    return 0.0;
  }

  float t = (fogMax - dist) / (fogMax - fogMin);

  return 1.0 - t;
}

void main(void) {
  gl_FragColor = vColor;
  gl_FragColor *= vec4(vLighting, 1.0);

  gl_FragColor = mix(
    gl_FragColor,
    vec4(0.0, 0.0, 0.0, 1.0),
    fogFactor(10.0, 50.0, 0.01)
  );
}
