#version 120

varying vec3 vColor;

void main() {
  // gl_FragColor = vec4(mix(vColor, vec3(1.0, 1.0, 1.0), 0.5), 1.0);
  gl_FragColor = vec4(vColor, 1.0);
}
