#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 model;
uniform mat4 vp;

out vec3 n;
out vec2 tc;

void main()
{
    gl_Position = vp * model * vec4(position, 1.f);
    n = normal;
    tc = texCoords;
}
