#version 120

uniform sampler2D uTexture;
uniform bool uColorTexture;

varying vec2 vTexCoords;

void main() {
  if (uColorTexture) {
    gl_FragColor = texture2D(uTexture, vTexCoords);
  } else {
    float x = texture2D(uTexture, gl_FragCoord.xy / vec2(800.0, 600.0)).r * 0.95;
    x = pow(x, 10);
    gl_FragColor = vec4(x, x, x, 1.0);
  }
}
