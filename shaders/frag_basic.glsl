#version 460 core

out vec4 fragColor;
in vec3 n;
in vec2 tc;

uniform sampler2D tex;

void main()
{
    vec4 color = texture(tex, tc);
    if (color.a < 0.01f)
        discard;

    fragColor = color;
}
