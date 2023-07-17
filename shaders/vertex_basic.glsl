#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 col;

out vec4 color;

void main()
{
    gl_Position = vec4(pos, 1.f);
    color = col;
}
