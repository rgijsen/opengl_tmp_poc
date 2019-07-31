R"(
#version 420 core

in vec4 point;
in vec4 color;

uniform mat4 mvp_matrix;

out vec4 fragmentColor;

void main()
{
    gl_Position = mvp_matrix * point;
    fragmentColor = color;
}
)"
