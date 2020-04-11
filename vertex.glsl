#version 330 core
layout (location = 0) in vec3 position;

out vec4 vertexColor;
float shift_factor = 0.0;

void main()
{
    gl_Position = vec4(position, 1.0);
    vertexColor = vec4(position.x + shift_factor, position.y + shift_factor,0.0, 1.0);
}