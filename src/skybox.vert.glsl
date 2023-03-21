#version 330 core
layout (location = 0) in vec4 pos;

out vec3 texCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
  texCoord = pos.xyz;
  gl_Position = projection * view * pos;
}
