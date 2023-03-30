#version 330 core

in vec4 vertexColor;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec4 color;

void main()
{
  color = vertexColor;
}
