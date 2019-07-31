R""(
#version 440 core

uniform vec4 fragmentColor;
out vec3 g_color;

void main()
{
    //g_color = vec3(1, 1, 0);
    g_color = fragmentColor.xyz;
}
)""