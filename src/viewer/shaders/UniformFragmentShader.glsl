R""(
#version 440 core

uniform vec4 fragmentColor;
out vec4 g_color;

void main()
{
    //g_color = vec4(1, 1, 0, 1);
    g_color = fragmentColor;
}
)""