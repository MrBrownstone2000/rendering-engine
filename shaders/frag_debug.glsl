#version 460 core

out vec4 fragColor;
in vec3 n;
in vec2 tc;

uniform int debugMode;

void main()
{
    vec4 color;
    switch (debugMode)
    {
        case 0:
            color = vec4(abs(n), 1);
            break;
        case 1:
            color = vec4(tc, 0, 1);
            break;
    }
    fragColor = color;
}

