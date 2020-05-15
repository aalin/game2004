#version 120

varying vec4 vColor;
uniform sampler2D uDepthTexture;
uniform int uWidth;
uniform int uHeight;

void main() {
  vec2 uv = gl_FragCoord.xy / vec2(uWidth, uHeight);
  float depth = texture2D(uDepthTexture, uv).r;

  if (gl_FragCoord.z < depth) {
    gl_FragColor = vColor;
  } else {
    discard;
  }
}
