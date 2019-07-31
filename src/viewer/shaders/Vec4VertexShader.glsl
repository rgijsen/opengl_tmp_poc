R"(
#version 440 core

in vec4 point;

uniform mat4 mvp_matrix;

void main()
{
    gl_Position = mvp_matrix * point;
}
)"
