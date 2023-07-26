#version 460 core

out vec4 FragColor;
in vec3 n;
in vec2 tc;

void main()
{
    FragColor = vec4(tc, 1-tc.x-tc.y, 1);
}
