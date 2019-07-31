R"(
#version 440 core

in vec2 point;

uniform mat4 viewMatrix;

void main()
{
    gl_Position = viewMatrix * vec4(point, 0.0, 1.0);
}
)"
