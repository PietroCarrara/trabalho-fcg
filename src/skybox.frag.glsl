#version 330 core
out vec4 color;

in vec3 texCoord;

uniform samplerCube skybox;

uniform float time;
uniform float noisiness;

float random (vec2 st) {
  return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43757.441);
}

void main()
{
  color.rgb = texture(skybox, texCoord).rgb;
  color.a = 1;

  // Slender noise
  color.rgb = mix(color.rgb, vec3(random(vec2((texCoord.xy) * time))), noisiness);

  // Cor final com correção gamma, considerando monitor sRGB.
  color.rgb = pow(color.rgb, vec3(1)/2.2);
}
