#version 330 core

layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 normal_coefficients;
layout (location = 2) in vec2 texture_coefficients;
layout (location = 3) in vec4 color_coefficients;
layout (location = 4) in int texture_index;

out vec4 vertexColor;
out vec4 positionWorld;
out vec4 normal;
out vec2 texCoord;
flat out int textureIndex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 viewVec;

void main()
{
    gl_Position = projection * view * model * model_coefficients;
    vertexColor = color_coefficients;

    positionWorld = model * model_coefficients;

    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;

    textureIndex = texture_index;

    texCoord = texture_coefficients;
}

