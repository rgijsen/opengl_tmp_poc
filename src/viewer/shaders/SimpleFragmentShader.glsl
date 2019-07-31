R"(
#version 420 core

in vec4 fragmentColor;
out vec4 g_color;

void main()
{
    g_color = fragmentColor;
    //g_color = vec4(1.0, 0.0, 0.0, 1.0);
}
)"