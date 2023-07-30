#version 460 core

out vec4 FragColor;
in vec3 n;
in vec2 tc;

uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, tc);
}
